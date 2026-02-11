write_pattern_db(FILE *outfile)
{
  if (database_type == DB_CORNER) {
    fprintf(outfile, "struct corner_db %s_db = {\n", prefix);
    fprintf(outfile, "  %d,\n", corner_max_width + 1);
    fprintf(outfile, "  %d,\n", corner_max_height + 1);
    fprintf(outfile, "  %d,\n", corner_root.num_variations);
    fprintf(outfile, "  %s_variations\n", prefix);
    fprintf(outfile, "};\n");

    return;
  }


  fprintf(outfile, "\n");
  fprintf(outfile, "struct pattern_db %s_db = {\n", prefix);
  fprintf(outfile, "  -1,\n");
  fprintf(outfile, "  %d,\n", fixed_anchor);
  fprintf(outfile, "  %s\n", prefix);
  if (database_type == DB_DFA)
    fprintf(outfile, " ,& dfa_%s\n", prefix);
  else
    fprintf(outfile, " , NULL\n");

  fprintf(outfile, "};\n");
}
