dsgw_html_begin( char *title, int titleinbody )
{
    static int	header_done = 0;

    if ( !header_done ) {
	dsgw_emits( "<!DOCTYPE html PUBLIC \"-//W3C//DTD HTML 4.01//EN\"\n" );
	dsgw_emits( "    \"http://www.w3.org/TR/html4/strict.dtd\">\n" );
	dsgw_emits( "<HTML>" );
	dsgw_head_begin();
	dsgw_emits( "\n" );
	if ( title != NULL ) {
	    dsgw_emitf( "<TITLE>%s</TITLE>\n", title );
	} else {
	    dsgw_emitf( "<TITLE>TITLE</TITLE>\n" );
	}
	dsgw_emitf( "</HEAD>\n<BODY %s>\n", dsgw_html_body_colors );
    } else {
	dsgw_emits( "\n<HR>\n" );
    }

    if (( title != NULL ) && ( header_done || titleinbody )) {
	dsgw_emitf( "<CENTER><TABLE BORDER=\"2\" CELLPADDING=\"10\" WIDTH=100%%>\n"
		"<TR><TD ALIGN=\"center\" WIDTH=\"100%%\">\n<FONT SIZE=\"+2\">"
		"<B>%s</B></FONT></TD></TR></TABLE></CENTER>\n<br>\n", title );
    }

    header_done = 1;
}
