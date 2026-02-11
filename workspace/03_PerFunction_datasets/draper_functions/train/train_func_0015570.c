write_next_state_function_uncompressed(int Nt)
{
  extern char *prefix;
  if (prefix) {
    fprintf(output, "int %s_next_state(int current_state, int next_token) {\n", prefix);
    fprintf(output, "  if (next_token < 0 || next_token >= %d) return -1;\n", Nt);
    fprintf(output, "  return %s_trans[%d*current_state + next_token];\n", prefix, Nt);
    fprintf(output, "}\n");
  } else {
    fprintf(output, "int next_state(int current_state, int token) {\n");
    fprintf(output, "  if (next_token < 0 || next_token >= %d) return -1;\n", Nt);
    fprintf(output, "  return trans[%d*current_state + next_token];\n", Nt);
    fprintf(output, "}\n");
  }
}
