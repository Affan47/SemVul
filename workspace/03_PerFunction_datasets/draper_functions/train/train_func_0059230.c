c_fclose(void *_fh)
{     FILE *fh = _fh;
      int ret;
      if (fh == stdin)
         ret = 0;
      else if (fh == stdout || fh == stderr)
         fflush(fh), ret = 0;
      else
         ret = fclose(fh);
      if (ret != 0)
      {  lib_err_msg(strerror(errno));
         ret = XEOF;
      }
      return ret;
}
