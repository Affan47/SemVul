inp_line(fd, buf, size)
int fd;
char * buf;
int size;
{
   int offt = 0;
   if( fd!=lastfd ) inp_seek(-1, 0L);
   for(;;)
   {
      if(in_start >= in_end)
      {
	 lastfd = -1;
         ftpos = lseek(fd, 0L, 1);
	 in_start = 0;
         in_end = read(fd, input_buf, sizeof(input_buf));
	 if( in_end <=0 ) return in_end;
	 lastfd = fd;
      }
      if( (buf[offt++] = input_buf[in_start++]) == '\n' || offt >= size )
         break;
   }
   return offt;
}
