ProcessFile(const char *d,const FileInfo *fi)
{
   if(buf->Broken())
      return PRF_FATAL;
   if(buf->Error())
   {
      eprintf("%s: %s\n",op,buf->ErrorText());
      return PRF_FATAL;
   }
   if(fg_data==0)
      fg_data=buf->GetFgData(fg);
   if(buf->Size()>0x10000)
      return PRF_LATER;

   if(fi->filetype==fi->DIRECTORY)
      return PRF_OK;
   if(!file_count && !(fi->defined&fi->SIZE))
      return PRF_OK;


   long long add = fi->size;
   if (file_count)
      add = 1;
   if(size_stack.count()>0)
      size_stack.last()->size += add;
   tot_size += add;

   if(all_files || stack_ptr == -1) {

      if(max_print_depth == -1 || stack_ptr < max_print_depth)
	 print_size(fi->size, MakeFileName(fi->name));
   }

   return PRF_OK;
}
