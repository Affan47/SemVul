disp_help_url(const fl_vecs_t* vec, arglist_t* arg)
{
  printf("\t" WEB_DOC_DIR "/fmt_%s.html", vec->name);
  if (arg) {
    printf("#fmt_%s_o_%s",vec->name, arg->argstring);
  }
}
