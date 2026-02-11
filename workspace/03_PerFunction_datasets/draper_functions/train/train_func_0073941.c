Free_gmtmath_Ctrl (struct GMTMATH_CTRL *C) {
	if (C->A.file) free ((void *)C->A.file);
	GMT_free ((void *)C->C.cols);
	GMT_free ((void *)C->F.cols);
	if (C->T.file) free ((void *)C->T.file);
	GMT_free ((void *)C);
}
