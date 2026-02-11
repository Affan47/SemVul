save_specs(void)
{
  char* filename;
  FILE* fp;

  filename = str_concat(str_dup(temp_dir), "/SPECS");
  if ((fp = fopen(filename, "wb")) == NULL) {
    cmd_error("failed to write file: %s : %s\n", filename, strerror(errno));
  }
  fwrite(spec, 1, spec_size, fp);
  fclose(fp);
  free(filename);
}
