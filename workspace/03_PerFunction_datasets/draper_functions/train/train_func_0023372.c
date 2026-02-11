SendArrayInfoRequests()
{
   for(int i=fileset_for_info->curr_index(); i<fileset_for_info->count(); i++)
   {
      FileInfo *fi=(*fileset_for_info)[i];
      if(fi->need)
      {
	 const char *e=shell_encode(fi->name);
	 Send("#INFO %s\n"
	      "ls -lLd %s; echo '### 200'\n",fi->name.get(),e);
	 PushExpect(EXPECT_INFO);
      }
   }
}
