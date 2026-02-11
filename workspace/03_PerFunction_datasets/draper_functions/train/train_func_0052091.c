au_whtmp_lkup(struct dentry *h_parent, struct au_branch *br,
			     struct qstr *prefix)
{
	struct dentry *dentry;
	int i;
	char defname[NAME_MAX - AUFS_MAX_NAMELEN + DNAME_INLINE_LEN + 1],
		*name, *p;

	static unsigned short cnt;
	struct qstr qs;

	BUILD_BUG_ON(sizeof(cnt) * 2 > AUFS_WH_TMP_LEN);

	name = defname;
	qs.len = sizeof(defname) - DNAME_INLINE_LEN + prefix->len - 1;
	if (unlikely(prefix->len > DNAME_INLINE_LEN)) {
		dentry = ERR_PTR(-ENAMETOOLONG);
		if (unlikely(qs.len > NAME_MAX))
			goto out;
		dentry = ERR_PTR(-ENOMEM);
		name = kmalloc(qs.len + 1, GFP_NOFS);
		if (unlikely(!name))
			goto out;
	}


	memcpy(name, AUFS_WH_PFX AUFS_WH_PFX, AUFS_WH_PFX_LEN * 2);
	p = name + AUFS_WH_PFX_LEN * 2;
	memcpy(p, prefix->name, prefix->len);
	p += prefix->len;
	*p++ = '.';
	AuDebugOn(name + qs.len + 1 - p <= AUFS_WH_TMP_LEN);

	qs.name = name;
	for (i = 0; i < 3; i++) {
		sprintf(p, "%.*x", AUFS_WH_TMP_LEN, cnt++);
		dentry = au_sio_lkup_one(&qs, h_parent);
		if (IS_ERR(dentry) || d_is_negative(dentry))
			goto out_name;
		dput(dentry);
	}

	dentry = ERR_PTR(-EEXIST);
	AuDbg("%.*s\n", AuLNPair(&qs));
	BUG();

out_name:
	if (name != defname)
		kfree(name);
out:
	AuTraceErrPtr(dentry);
	return dentry;
}
