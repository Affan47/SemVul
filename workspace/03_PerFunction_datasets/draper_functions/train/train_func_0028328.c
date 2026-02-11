csio_ln_exit(struct csio_lnode *ln)
{
	struct csio_lnode *pln;

	csio_cleanup_rns(ln);
	if (csio_is_npiv_ln(ln)) {
		pln = csio_parent_lnode(ln);
		kref_put(&pln->fcfinfo->kref, csio_free_fcfinfo);
	} else {
		kref_put(&ln->fcfinfo->kref, csio_free_fcfinfo);
		if (csio_fdmi_enable)
			csio_ln_fdmi_exit(ln);
	}
	ln->fcfinfo = NULL;
}
