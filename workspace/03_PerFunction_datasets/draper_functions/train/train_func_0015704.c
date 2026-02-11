append_de(struct au_vdir *vdir, char *name, int nlen, ino_t ino,
		     unsigned int d_type, struct au_nhash *delist)
{
	int err;
	unsigned int sz;
	const unsigned int deblk_sz = vdir->vd_deblk_sz;
	union au_vdir_deblk_p p, *room, deblk_end;
	struct au_vdir_dehstr *dehstr;

	p.deblk = last_deblk(vdir);
	deblk_end.deblk = p.deblk + deblk_sz;
	room = &vdir->vd_last.p;
	AuDebugOn(room->deblk < p.deblk || deblk_end.deblk <= room->deblk
		  || !is_deblk_end(room, &deblk_end));

	sz = calc_size(nlen);
	if (unlikely(sz > deblk_end.deblk - room->deblk)) {
		err = append_deblk(vdir);
		if (unlikely(err))
			goto out;

		p.deblk = last_deblk(vdir);
		deblk_end.deblk = p.deblk + deblk_sz;

		AuDebugOn(room->deblk != p.deblk);
	}

	err = -ENOMEM;
	dehstr = au_cache_alloc_vdir_dehstr();
	if (unlikely(!dehstr))
		goto out;

	dehstr->str = &room->de->de_str;
	hlist_add_head(&dehstr->hash, au_name_hash(delist, name, nlen));
	room->de->de_ino = ino;
	room->de->de_type = d_type;
	room->de->de_str.len = nlen;
	memcpy(room->de->de_str.name, name, nlen);

	err = 0;
	room->deblk += sz;
	if (unlikely(set_deblk_end(room, &deblk_end)))
		err = append_deblk(vdir);


out:
	return err;
}
