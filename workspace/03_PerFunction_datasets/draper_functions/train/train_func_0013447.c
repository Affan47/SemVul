PutEpsFile(char *s, double height0, double width0, double scale, double baseline)
{
    char *png;

    if (g_figure_include_converted) {
    	diagnostics(WARNING, "Rendering '%s'", s);
		  diagnostics(3,"Converting EPS to PNG and inserting in RTF.");
        png = eps_to_png(s);
        if (png) {
            PutPngFile(png, height0, width0, scale, baseline);
            my_unlink(png);
            free(png);
        }
    }

    if (g_figure_comment_converted) {
		  diagnostics(3,"Inserting EPS file name in text");
		  putRtfStrEscaped("[###");
		  putRtfStrEscaped(s);
		  putRtfStrEscaped("###]");
    }
}
