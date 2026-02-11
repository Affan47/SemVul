PSPageTerm(GPSWindow ps, int last) {
    GPSDisplay *gdisp = (GPSDisplay *) (ps->display);
    int thumb_per_page = gdisp->linear_thumb_cnt*gdisp->linear_thumb_cnt;

    _GPSDraw_FlushPath(ps);
    if ( gdisp->eps )
return;
    if ( last || ps->page_cnt%thumb_per_page==0 ) {
	fprintf( ps->output_file, "%%%%PageTrailer\n" );
	if ( last )
	    fprintf( ps->output_file, "g_finalpage\t\t%%End of Page\n" );
	else
	    fprintf( ps->output_file, "g_endpage\t\t%%End of Page\n" );
	fprintf( ps->output_file, "%%%%EndPageTrailer\n" );
    } else
	fprintf( ps->output_file, "g_endpage\t\t%%End of Psuedo Page\n" );
}
