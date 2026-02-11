influence_values_report_streams( clsf_DS clsf, search_DS search, int num_atts_to_list,
                                      shortstr report_mode, char *influ_vals_file_ptr,
                                      char *results_file_ptr, int clsf_num, clsf_DS test_clsf,
                                      unsigned int order_attributes_by_influence_p,
                                      unsigned int comment_data_headers_p,
                                      int_list sigma_contours_att_list)
{
  static fxlstr influence_report_pathname;
  char clsf_num_string[4];
  FILE *influence_report_fp = NULL;
  int header_information_p = FALSE, num_chars_to_trunc = 5, trunc_index;
  fxlstr str;
  char caller[] = "influence_values_report_streams";

  influence_report_pathname[0] = clsf_num_string[0] = '\0';

  strcpy( influence_report_pathname, influ_vals_file_ptr);

  trunc_index = (int) strlen( influence_report_pathname) - num_chars_to_trunc;
  influence_report_pathname[trunc_index] = '\0';
  if (order_attributes_by_influence_p == TRUE)
    strcat( influence_report_pathname, "o-");
  else
    strcat( influence_report_pathname, "no-");

  if (eqstring (report_mode, "text") == TRUE)
    strcat( influence_report_pathname, "text-");
  else if (eqstring (report_mode, "data") == TRUE)
    strcat( influence_report_pathname, "data-");
  sprintf( clsf_num_string, "%d", clsf_num);
  strcat( influence_report_pathname, clsf_num_string);
  if (num_atts_to_list == ALL_ATTRIBUTES)
    num_atts_to_list = clsf->database->n_atts;
  else
    num_atts_to_list = max( 1, min( num_atts_to_list, clsf->database->n_atts));

  influence_report_fp = fopen( influence_report_pathname, "w");

  autoclass_influence_values_report( clsf, search, num_atts_to_list, results_file_ptr,
                                     header_information_p, influence_report_fp,
                                     report_mode , test_clsf,
                                     order_attributes_by_influence_p,
                                     comment_data_headers_p,
                                     sigma_contours_att_list);

  fclose( influence_report_fp);

  safe_sprintf( str, sizeof( str), caller,
               "\nFile written: %s%s\n",
          (influence_report_pathname[0] == G_slash) ? "" : G_absolute_pathname,
          influence_report_pathname);
  to_screen_and_log_file(str, G_log_file_fp, G_stream, TRUE);
}
