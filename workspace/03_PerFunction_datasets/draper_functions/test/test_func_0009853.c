dispatch_filehandlers(int nfh, fd_set *fhs)
{
  int fh = 0;

  while (nfh > 0) {
    if (FD_ISSET(fh, fhs)) {


      (file_handlers[fh].handler)(file_handlers[fh].arg);


      --nfh;
    }

    ++fh;
  }

}
