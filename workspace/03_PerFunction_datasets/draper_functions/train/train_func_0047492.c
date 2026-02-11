read_dir(struct sar_file *out, mode_t mode)
{
  if(out->list_only)
    return;


  if(mkdir(out->wp, mode) < 0 && errno != EEXIST)
    warn("cannot create directory \"%s\"", out->wp);
}
