jffs2_garbage_collect_deletion_dirent(struct jffs2_sb_info *c, struct jffs2_eraseblock *jeb,
					struct jffs2_inode_info *f, struct jffs2_full_dirent *fd)
{
	struct jffs2_full_dirent **fdp = &f->dents;
	int found = 0;


	if (!jffs2_can_mark_obsolete(c)) {
		struct jffs2_raw_dirent *rd;
		struct jffs2_raw_node_ref *raw;
		int ret;
		size_t retlen;
		int name_len = strlen(fd->name);
		uint32_t name_crc = crc32(0, fd->name, name_len);
		uint32_t rawlen = ref_totlen(c, jeb, fd->raw);

		rd = kmalloc(rawlen, GFP_KERNEL);
		if (!rd)
			return -ENOMEM;


		mutex_lock(&c->erase_free_sem);

		for (raw = f->inocache->nodes; raw != (void *)f->inocache; raw = raw->next_in_ino) {

			cond_resched();


			if (!(ref_obsolete(raw)))
				continue;


			if (ref_totlen(c, NULL, raw) != rawlen)
				continue;


			if (SECTOR_ADDR(raw->flash_offset) == SECTOR_ADDR(fd->raw->flash_offset))
				continue;

			jffs2_dbg(1, "Check potential deletion dirent at %08x\n",
				  ref_offset(raw));


			ret = jffs2_flash_read(c, ref_offset(raw), rawlen, &retlen, (char *)rd);
			if (ret) {
				pr_warn("%s(): Read error (%d) reading obsolete node at %08x\n",
					__func__, ret, ref_offset(raw));

				continue;
			}
			if (retlen != rawlen) {
				pr_warn("%s(): Short read (%zd not %u) reading header from obsolete node at %08x\n",
					__func__, retlen, rawlen,
					ref_offset(raw));
				continue;
			}

			if (je16_to_cpu(rd->nodetype) != JFFS2_NODETYPE_DIRENT)
				continue;


			if (je32_to_cpu(rd->name_crc) != name_crc)
				continue;


			if (rd->nsize != name_len || !je32_to_cpu(rd->ino))
				continue;


			if (memcmp(rd->name, fd->name, name_len))
				continue;


			mutex_unlock(&c->erase_free_sem);

			jffs2_dbg(1, "Deletion dirent at %08x still obsoletes real dirent \"%s\" at %08x for ino #%u\n",
				  ref_offset(fd->raw), fd->name,
				  ref_offset(raw), je32_to_cpu(rd->ino));
			kfree(rd);

			return jffs2_garbage_collect_dirent(c, jeb, f, fd);
		}

		mutex_unlock(&c->erase_free_sem);
		kfree(rd);
	}


	while (*fdp) {
		if ((*fdp) == fd) {
			found = 1;
			*fdp = fd->next;
			break;
		}
		fdp = &(*fdp)->next;
	}
	if (!found) {
		pr_warn("Deletion dirent \"%s\" not found in list for ino #%u\n",
			fd->name, f->inocache->ino);
	}
	jffs2_mark_node_obsolete(c, fd->raw);
	jffs2_free_full_dirent(fd);
	return 0;
}
