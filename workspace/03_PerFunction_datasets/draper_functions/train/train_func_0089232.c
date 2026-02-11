xcf_read_int32(void     *fp,
               DATA32   *data,
               int       count)
{
   int total;

   total = count;
   if (count > 0)
     {
        xcf_read_int8(fp, (DATA8*) data, count * 4);
        while (count--)
          {
             *data = (DATA32)ntohl(*data);
             data++;
          }
     }
   return total * 4;
}
