make_directory(const char *d_c)
{
   if(!make_dirs)
      return;
   char *d=alloca_strdup(d_c);
   char *slash=strrchr(d,'/');
   if(!slash || slash==d)
      return;

   *slash=0;

   const char *dir_name_c=output_file_name(d,0,!reverse,output_dir,make_dirs);
   char *dir_name;
   if(dir_name_c==0 || dir_name_c[0]==0)
      return;
   dir_name=alloca_strdup(dir_name_c);
   if(reverse || url::is_url(dir_name))
   {
      if(mkdir_args)
      {
	 int j;
	 for(j=mkdir_base_arg; j<mkdir_args->count(); j++)
	    if(!strcmp(dir_name,mkdir_args->getarg(j)))
	       break;
	 if(j<mkdir_args->count())
	    return;
      }
      if(!mkdir_args)
      {
	 mkdir_args=new ArgV("mkdir");
	 mkdir_args->Append("-p");
	 mkdir_args->Append("--");
	 mkdir_base_arg=mkdir_args->count();
      }
      mkdir_args->Append(dir_name);
   }
   else
   {
      create_directories(dir_name);
   }
}
