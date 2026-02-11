_cfsml_write_sys_strings_t(FILE *fh, sys_strings_t* save_struc)
{
  int min, max, i;

  fprintf(fh, "{\n");
  fprintf(fh, "strings = ");
    min = max = SYS_STRINGS_MAX;
    fprintf(fh, "[%d][\n", max);
    for (i = 0; i < min; i++) {
      _cfsml_write_sys_string_t(fh, &(save_struc->strings[i]));
      fprintf(fh, "\n");
    }
    fprintf(fh, "]");
    fprintf(fh, "\n");
  fprintf(fh, "}");
}
