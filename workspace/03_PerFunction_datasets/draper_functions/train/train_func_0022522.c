read_string_pattern (NODE_T * p, MOID_T * m, A68_REF ref_file)
{
  for (; p != NO_NODE; FORWARD (p)) {
    if (IS (p, INSERTION)) {
      read_insertion (SUB (p), ref_file);
    } else if (IS (p, FORMAT_ITEM_A)) {
      scan_n_chars (p, 1, m, ref_file);
    } else if (IS (p, FORMAT_ITEM_S)) {
      add_char_transput_buffer (p, INPUT_BUFFER, BLANK_CHAR);
      return;
    } else if (IS (p, REPLICATOR)) {
      int j, k = get_replicator_value (SUB (p), A68_TRUE);
      for (j = 1; j <= k; j++) {
        read_string_pattern (NEXT (p), m, ref_file);
      }
      return;
    } else {
      read_string_pattern (SUB (p), m, ref_file);
    }
  }
}
