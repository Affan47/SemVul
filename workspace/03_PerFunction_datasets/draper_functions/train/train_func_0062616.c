output_file_close(FILE *f){
  if( f && f!=stdout && f!=stderr ) fclose(f);
}
