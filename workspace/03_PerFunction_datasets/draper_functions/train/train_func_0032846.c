arc_delete(void) {

    if (lseek(arcfile,thisheader,SEEK_SET)<0)
      error(1,ERR_SEEK,"arc_delete()");
    if (write(arcfile,"\xff",1)!=1) error(1,ERR_WRITE,arcname);
    if (lseek(arcfile,2,SEEK_SET)<0) error(1,ERR_SEEK,"arc_delete()");
    putvalue(--arccnt,2);
    dirty=1;
}
