flush(void)
{
   while (bufptr > buf)
      shift_first_out();
}
