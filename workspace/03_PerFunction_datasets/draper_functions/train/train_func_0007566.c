Free_grdlandmask_Ctrl (struct GRDLANDMASK_CTRL *C) {
	if (C->G.file) free ((void *)C->G.file);
	GMT_free ((void *)C);
}
