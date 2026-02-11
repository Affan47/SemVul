Free_ps2raster_Ctrl (struct PS2RASTER_CTRL *C) {
	if (C->D.dir) free ((void *)C->D.dir);
	if (C->F.file) free ((void *)C->F.file);
	if (C->G.file) free ((void *)C->G.file);
	if (C->L.file) free ((void *)C->L.file);
	free ((void *)C->W.doctitle);
	free ((void *)C->W.overlayname);
	if (C->W.URL) free ((void *)C->W.URL);
	GMT_free ((void *)C);
}
