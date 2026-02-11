PutPdfFile(char *s, double height0, double width0, double scale, double baseline)
{
    char *png, *pdf, *eps, *out, *tmp_dir;

    if (g_figure_include_converted) {
		diagnostics(WARNING, "Rendering '%s'", s);
		diagnostics(3,"Converting PDF to PNG and inserting into RTF.");

		png = pdf_to_png(s);

		if (png) {
			PutPngFile(png, height0, width0, scale, baseline);
			my_unlink(png);
			safe_free(png);
		}
    }

    if (g_figure_comment_converted) {
       diagnostics(3,"Converting PDF to EPS and inserting file name in text");
       eps = strdup_new_extension(s, ".pdf", ".eps");
       if (eps == NULL) {
           eps = strdup_new_extension(s, ".PDF", ".eps");
           if (eps == NULL) {
		          diagnostics(ERROR,"PutPdfFile: Graphicsfile hat not .pdf extension");
              return;
           }
       }

       tmp_dir = getTmpPath();
       pdf = strdup_together(g_home_dir, s);
       out = SysGraphicsConvert(CONVERT_PS_TO_EPS, 0, g_dots_per_inch, pdf, eps);

       if (out != NULL) {
           eps = strdup_together(tmp_dir, eps);
           putRtfStrEscaped("[###");
           putRtfStrEscaped(eps);
           putRtfStrEscaped("###]");
           free(out);
       }
       free (tmp_dir);
       free (pdf);
       free (eps);
    }
}
