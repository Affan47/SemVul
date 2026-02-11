clean_exit()
{

  if(opt_value->cwd) {
    xchdir(opt_value->cwd);
    free(opt_value->cwd);
  }
}
