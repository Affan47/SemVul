input_cgraph_opt_summary (VEC (cgraph_node_ptr, heap) * nodes)
{
  struct lto_file_decl_data **file_data_vec = lto_get_file_decl_data ();
  struct lto_file_decl_data *file_data;
  unsigned int j = 0;

  while ((file_data = file_data_vec[j++]))
    {
      size_t len;
      const char *data =
	lto_get_section_data (file_data, LTO_section_cgraph_opt_sum, NULL,
			      &len);

      if (data)
	input_cgraph_opt_section (file_data, data, len, nodes);
    }
}
