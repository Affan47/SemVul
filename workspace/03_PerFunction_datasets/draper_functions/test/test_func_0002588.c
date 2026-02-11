gfile_file_on_seek(void *ud, gar_off_t off, jmp_buf env) {
  gfile_file_ud_t *fud = (gfile_file_ud_t *)ud;


  if (off > (unsigned long)fud->fsize) {
    _gar_error(env, fud->fname, "out-of-range seek offset");
  }

  if (fseek(fud->fp, (long)off, SEEK_SET)) { _gar_perror(env, fud->fname); }
}
