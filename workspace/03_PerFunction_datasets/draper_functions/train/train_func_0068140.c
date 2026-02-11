FTPType(fi)
FTPInfo *fi;
{

  if (fi->fp != NULL) fi->fp->good = true;
  snprintf (fi->request, sizeof(fi->request), "TYPE I\r\n");
  FTPSimple(fi, FTPSize, false);
  return;
}
