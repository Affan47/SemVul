MakeFileInfo(const NameAttrs *na)
{
   const FileAttrs *a=&na->attrs;
   const char *name=utf8_to_lc(na->name);
   const char *longname=utf8_to_lc(na->longname);

   LogNote(10,"NameAttrs(name=\"%s\",type=%d,longname=\"%s\")\n",name?name:"",a->type,longname?longname:"");

   if(!name || !name[0])
      return 0;
   if(strchr(name,'/'))
      return 0;
   if(name[0]=='~')
      name=dir_file(".",name);
   Ref<FileInfo> fi(new FileInfo(name));
   switch(a->type)
   {
   case SSH_FILEXFER_TYPE_REGULAR:
   case SSH_FILEXFER_TYPE_DIRECTORY:
   case SSH_FILEXFER_TYPE_SYMLINK:
   case SSH_FILEXFER_TYPE_UNKNOWN: break;
   default: return 0;
   }
   if(longname)
      fi->SetLongName(longname);
   MergeAttrs(fi.get_non_const(),a);
   if(fi->longname && !a->owner)
   {

      Ref<FileInfo> ls(FileInfo::parse_ls_line(fi->longname,0));
      if(ls)
      {
	 if(ls->user)
	    fi->SetUser(ls->user);
	 if(ls->group)
	    fi->SetGroup(ls->group);
	 if(ls->nlinks>0)
	    fi->SetNlink(ls->nlinks);
      }
   }
   return fi.borrow();
}
