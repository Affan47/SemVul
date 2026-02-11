GPrinterStartJob(GDisplay *gdisp,void *user_data,GPrinterAttrs *attrs) {
    if ( gdisp==NULL )
	gdisp = printer_display;
return( (gdisp->funcs->startJob)(gdisp,user_data,attrs) );
}
