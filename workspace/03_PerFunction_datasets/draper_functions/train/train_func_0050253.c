compute_output_file_names (void)
{
  compute_file_name_parts ();


  if (!src_extension)
    src_extension = xstrdup (".c");
  if (!header_extension)
    header_extension = xstrdup (".h");

  parser_file_name =
    (spec_outfile
     ? xstrdup (spec_outfile)
     : concat2 (all_but_ext, src_extension));

  if (defines_flag)
    {
      if (! spec_defines_file)
        spec_defines_file = concat2 (all_but_ext, header_extension);
    }

  if (graph_flag)
    {
      if (! spec_graph_file)
        spec_graph_file = concat2 (all_but_tab_ext, ".dot");
      output_file_name_check (&spec_graph_file, false);
    }

  if (xml_flag)
    {
      if (! spec_xml_file)
        spec_xml_file = concat2 (all_but_tab_ext, ".xml");
      output_file_name_check (&spec_xml_file, false);
    }

  if (report_flag)
    {
      if (!spec_verbose_file)
        spec_verbose_file = concat2 (all_but_tab_ext, OUTPUT_EXT);
      output_file_name_check (&spec_verbose_file, false);
    }

  free (all_but_tab_ext);
  free (src_extension);
  free (header_extension);
}
