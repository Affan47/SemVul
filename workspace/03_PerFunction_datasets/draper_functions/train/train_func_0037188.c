Append(const char *buf,int size)
{
   if(size==0)
      return;

   SaveMaxCheck(size);
   if(Size()==0 && buffer_ptr>0 && !save)
   {
      buffer.truncate(0);
      buffer_ptr=0;
   }

   memmove(GetSpace(size),buf,size);
   SpaceAdd(size);
}
