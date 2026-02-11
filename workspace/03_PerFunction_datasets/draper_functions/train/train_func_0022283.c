ivl_file_table_size()
{
      if (fn_vector.empty()) {
	    ivl_file_table_init();
      }

      return fn_vector.size();
}
