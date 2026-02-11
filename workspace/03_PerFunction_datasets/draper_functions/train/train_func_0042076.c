exfat_rename(struct exfat* ef, const char* old_path, const char* new_path)
{
	struct exfat_node* node;
	struct exfat_node* existing;
	struct exfat_node* dir;
	cluster_t cluster = EXFAT_CLUSTER_BAD;
	off_t offset = -1;
	le16_t name[EXFAT_NAME_MAX + 1];
	int rc;

	rc = exfat_lookup(ef, &node, old_path);
	if (rc != 0)
		return rc;

	rc = exfat_split(ef, &dir, &existing, name, new_path);
	if (rc != 0)
	{
		exfat_put_node(ef, node);
		return rc;
	}


	if (node->flags & EXFAT_ATTRIB_DIR)
	{
		struct exfat_node* p;

		for (p = dir; p; p = p->parent)
			if (node == p)
			{
				if (existing != NULL)
					exfat_put_node(ef, existing);
				exfat_put_node(ef, dir);
				exfat_put_node(ef, node);
				return -EINVAL;
			}
	}

	if (existing != NULL)
	{

		if (existing != node)
		{
			if (existing->flags & EXFAT_ATTRIB_DIR)
			{
				if (node->flags & EXFAT_ATTRIB_DIR)
					rc = exfat_rmdir(ef, existing);
				else
					rc = -ENOTDIR;
			}
			else
			{
				if (!(node->flags & EXFAT_ATTRIB_DIR))
					rc = exfat_unlink(ef, existing);
				else
					rc = -EISDIR;
			}
			exfat_put_node(ef, existing);
			if (rc != 0)
			{
				exfat_put_node(ef, dir);
				exfat_put_node(ef, node);
				return rc;
			}
		}
		else
			exfat_put_node(ef, existing);
	}

	rc = find_slot(ef, dir, &cluster, &offset,
			2 + DIV_ROUND_UP(utf16_length(name), EXFAT_ENAME_MAX));
	if (rc != 0)
	{
		exfat_put_node(ef, dir);
		exfat_put_node(ef, node);
		return rc;
	}
	rename_entry(ef, dir, node, name, cluster, offset);
	exfat_put_node(ef, dir);
	exfat_put_node(ef, node);
	return 0;
}
