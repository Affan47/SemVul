latex_initialise (GSList * opes_selectionnees, gchar * filename )
{
    gfloat colwidth, real_width;
    gint i, current_report_number;

    current_report_number = gsb_gui_navigation_get_current_report ();

    if ( etat.print_config.printer || etat.print_config.filetype == POSTSCRIPT_FILE )
    {
	tempname = g_strdup_printf ( "gsbpt%d", g_random_int_range (0,99999) );
	filename = g_strdup_printf ( "%s.tex", tempname );
    }
    else
    {
	filename = etat.print_config.printer_filename;
    }

    if ( ! filename )
    {
	filename = "";
    }

    g_unlink ( filename );
    file_out = utf8_fopen ( filename, "w" );
    if ( ! file_out )
    {
	dialogue_error ( g_strdup_printf (_("Cannot open file '%s': %s."), filename, g_strerror ( errno ) ) );
	return FALSE;
    }

    fprintf (file_out,
	     "\\documentclass{article}\n\n"
	     "\\special{! TeXDict begin /landplus90{true}store end }\n"
	     "\\usepackage{a4}\n"
	     "\\usepackage{eurosym}\n"
	     "\\usepackage{boxedminipage}\n"
	     "\\usepackage{longtable}\n"
	     "\\usepackage{vmargin}\n"
	     "\\usepackage[T1]{fontenc}\n"
	     "\\usepackage{ucs}\n"
	     "\\usepackage[utf8x]{inputenc}\n" );

    if ( etat.print_config.orientation == LANDSCAPE )
    {
	fprintf (file_out, "\\usepackage{portland}\n");
    }

    fprintf (file_out,
	     "\\setpapersize{%s}\n"
	     "\\setmarginsrb{1cm}{1cm}{1cm}{1cm}{0cm}{0cm}{0cm}{0cm}\n\n"
	     "\\begin{document}\n\n", etat.print_config.paper_config.name);

    if ( etat.print_config.orientation == LANDSCAPE )
      {
	fprintf (file_out, "\\landscape\n\n");
      }

    fprintf (file_out,
	     "\\fboxsep \\parskip\n"
	     "\\fboxrule 0pt\n"
	     "\\tabcolsep 0pt\n"
	     "\\begin{longtable}[l]{" );

    if ( etat.print_config.orientation == LANDSCAPE )
    {
	real_width = ((etat.print_config.paper_config.height-20)/10);
    }
    else
    {
	real_width = ((etat.print_config.paper_config.width-20)/10);
    }

    if ( gsb_data_report_get_show_report_transactions (current_report_number))
    {
	colwidth = real_width / ((float) (nb_colonnes / 2) + 1 );
	fprintf ( file_out, "p{%fcm}", colwidth);
	for (i = 0 ; i < nb_colonnes/2 ; i++)
	{
	    fprintf ( file_out, "p{%fcm}p{1pt}", colwidth );
	}
	fprintf ( file_out, "}" );
    }
    else
    {
	colwidth = real_width / (float) nb_colonnes;
	for (i = 0 ; i < nb_colonnes ; i++)
	{
	    fprintf (file_out, "p{%fcm}", colwidth);
	}
	fprintf (file_out, "p{1pt}}\n");
    }

    return TRUE;
}
