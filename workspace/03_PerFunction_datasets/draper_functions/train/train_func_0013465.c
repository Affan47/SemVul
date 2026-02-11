knocker_output_ports_info (int sp, int ep)
{
  if (!knocker_args.fency)
    {
      knocker_term_color_fprintf (knocker_output_fp, "\n", KNOCKER_COLOR_2, KNOCKER_COLOR_2_ATTR);
      return;
    }
  knocker_term_color_fprintf (knocker_output_fp, " - - scan from port: ", KNOCKER_COLOR_1, KNOCKER_COLOR_1_ATTR);
  knocker_term_color_intfprintf (knocker_output_fp, sp, KNOCKER_COLOR_2, KNOCKER_COLOR_2_ATTR);
  knocker_term_color_fprintf (knocker_output_fp, "\n - - - scan to port: ", KNOCKER_COLOR_1, KNOCKER_COLOR_1_ATTR);
  knocker_term_color_intfprintf (knocker_output_fp, ep, KNOCKER_COLOR_2, KNOCKER_COLOR_2_ATTR);
  knocker_term_color_fprintf (knocker_output_fp, "\n - - - -  scan type: ", KNOCKER_COLOR_1, KNOCKER_COLOR_1_ATTR);
  knocker_term_color_fprintf (knocker_output_fp, "tcp connect", KNOCKER_COLOR_2, KNOCKER_COLOR_2_ATTR);
  knocker_term_color_fprintf (knocker_output_fp, "\n\n+=- - - - - - - - - - - - - - - - - - - - - - - - - - - - - ",
                              KNOCKER_COLOR_1, KNOCKER_COLOR_1_ATTR);
  knocker_term_color_fprintf (knocker_output_fp, " s c a n n i n g ", KNOCKER_COLOR_2, KNOCKER_COLOR_2_ATTR);
  knocker_term_color_fprintf (knocker_output_fp, " -\n", KNOCKER_COLOR_1, KNOCKER_COLOR_1_ATTR);
  knocker_term_color_fprintf (knocker_output_fp, "\n", KNOCKER_COLOR_2, KNOCKER_COLOR_2_ATTR);

  fflush (knocker_output_fp);
}
