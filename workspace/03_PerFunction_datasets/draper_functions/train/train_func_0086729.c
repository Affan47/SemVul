xref_output_line_by_class( clsf_DS clsf, FILE *xref_class_report_fp,
                                shortstr report_mode,
                                shortstr **attribute_formats_ptr,
                                xref_data_DS xref_datum_ptr,
                                sort_cell_DS wt_class_pairs, int prob_tab,
                                int_list report_attribute_numbers,
                                unsigned int comment_data_headers_p)
{
  struct xref_data xref_datum = *xref_datum_ptr;
  int n_discrete_att = 0, n_real_att = 0, i, print_atts_p;
  att_DS *att_info = clsf->database->att_info;
  fxlstr prob_tab_format;
  char blank = ' ', char_s = 's', char_g = 'g', question_mark[] = "?";

  print_atts_p = (xref_datum.n_attribute_data > 0);
  if (print_atts_p == TRUE) {
    prob_tab += 4;
    sprintf( prob_tab_format, "\n%%%dc", prob_tab);
    strcat( prob_tab_format, "%2d  %5.3f");
  }
  if (eqstring (report_mode, "data") == TRUE)
    fprintf( xref_class_report_fp, "%03d", xref_datum.case_number);
  else
    fprintf( xref_class_report_fp, (print_atts_p == TRUE) ? "\n%6d" : "\n%11d",
             xref_datum.case_number);

  for (i=0; i<xref_datum.n_attribute_data; i++) {
    if (att_info[report_attribute_numbers[i]]->translations != NULL) {
      fprintf( xref_class_report_fp, (*attribute_formats_ptr)[i],
              xref_datum.discrete_attribute_data[n_discrete_att]);
      n_discrete_att++;
    }
    else {
      if (percent_equal( (double) xref_datum.real_attribute_data[n_real_att],
                        FLOAT_UNKNOWN, REL_ERROR) == TRUE) {

        (*attribute_formats_ptr)[i][strlen( (*attribute_formats_ptr)[i]) -1] =
          char_s;
        fprintf( xref_class_report_fp, (*attribute_formats_ptr)[i], question_mark);
      }
      else {
        (*attribute_formats_ptr)[i][strlen( (*attribute_formats_ptr)[i]) -1] =
          char_g;
        fprintf( xref_class_report_fp, (*attribute_formats_ptr)[i],
                xref_datum.real_attribute_data[n_real_att]);
      }
      n_real_att++;
    }
  }
  fprintf( xref_class_report_fp, "%s     %5.3f%s", (print_atts_p == TRUE) ? "   " : "",
          xref_datum.wt_class_pairs[0].float_value,
          (print_atts_p == TRUE) ? "" : "        ");
  for (i=1; i<xref_datum.n_collector; i++) {
    fprintf( xref_class_report_fp,
            (print_atts_p == TRUE) ? prob_tab_format : "%c%4d   %5.3f ", blank,
            xref_datum.wt_class_pairs[i].int_value,
            xref_datum.wt_class_pairs[i].float_value);
  }
  fprintf( xref_class_report_fp,"\n");
}
