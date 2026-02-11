DirFile(xstring& path,const xstring& ecwd,const xstring& efile) const
{
   const int base=path.length();

   if(efile[0]=='/') {
      path.append(efile);
   } else if(efile[0]=='~' || ecwd.length()==0 || (ecwd.eq("~") && !hftp)) {
      path.append('/');
      path.append(efile);
   } else {
      if(ecwd[0]!='/')
	 path.append('/');
      path.append(ecwd);
      if(ecwd.last_char()!='/' && efile.length()>0)
	 path.append('/');
      path.append(efile);
   }


   if(path[base+1]=='~' && path[base+2]==0)
      path.truncate(base+1);
   else if(path[base+1]=='~' && path[base+2]=='/')
      path.set_substr(base,2,"");
}
