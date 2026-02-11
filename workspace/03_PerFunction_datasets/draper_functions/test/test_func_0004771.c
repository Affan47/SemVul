buffreopen(long f_ofs, long file_recsize, long recnum,
		       long bl_size, char *rectype)
{
  char ebuff[200];
  long recsize;


  block_offset=f_ofs;
  block_size=bl_size;
  if (block_size % recnum !=0) {

      sprintf(ebuff,"Fractional record count in %s block.",rectype);
      agtwarn(ebuff,0);}
  buff_rsize=recsize=block_size/recnum;
  if (buff_rsize>file_recsize) buff_rsize=file_recsize;


  buffsize=BUFF_SIZE;
  if (block_size<buffsize) buffsize=block_size;


  if (buffsize<file_recsize) buffsize=file_recsize;
  if (buffsize<recsize) buffsize=recsize;

  rfree(buffer);
  buffer=rmalloc(buffsize);

  buff_setrecsize(recsize);
}
