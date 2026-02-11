au_ren_rev_diropq(int err, struct au_ren_args *a)
{
	int rerr;

	au_hn_imtx_lock_nested(a->src_hinode, AuLsc_I_CHILD);
	rerr = au_diropq_remove(a->src_dentry, a->btgt);
	au_hn_imtx_unlock(a->src_hinode);
	au_set_dbdiropq(a->src_dentry, a->src_bdiropq);
	if (rerr)
		RevertFailure("remove diropq %pd", a->src_dentry);
}
