copy_file(const char *srcfile, const char *dstfile)
{
  FILE *in,*out;
  unsigned char buf[COPY_BUF_SIZE];
  int r,w;
  int err=0;

  if (!srcfile || !dstfile) return -1;

  in=fopen(srcfile,"rb");
  if (!in) {
    warn("failed to open file for reading: %s", srcfile);
    return -2;
  }
  out=fopen(dstfile,"wb");
  if (!out) {
    fclose(in);
    warn("failed to open file for writing: %s", dstfile);
    return -3;
  }


  do {
    r=fread(buf,1,sizeof(buf),in);
    if (r > 0) {
      w=fwrite(buf,1,r,out);
      if (w != r) {
	err=1;
	warn("error writing to file: %s", dstfile);
	break;
      }
    } else {
      if (ferror(in)) {
	  err=2;
	  warn("error reading file: %s", srcfile);
	  break;
      }
    }
  } while (!feof(in));

  fclose(out);
  fclose(in);
  return err;
}
