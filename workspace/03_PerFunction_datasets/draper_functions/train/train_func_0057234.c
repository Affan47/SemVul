getstreamsize(void)
{
   if ( !sizeCached ) {
      struct stat buf;
      if ( stat ( getDeviceName().c_str(), &buf) )
         sizeValue = -1;
      else
         sizeValue = buf.st_size ;

      sizeCached = true;
   }
   return sizeValue;
}
