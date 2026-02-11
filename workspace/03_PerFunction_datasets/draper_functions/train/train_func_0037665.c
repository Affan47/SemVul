SaveItemListAsFile(struct Item *liststart,char *file,struct Attributes a,struct Promise *pp)

{ struct Item *ip;
  struct stat statbuf;
  char new[CF_BUFSIZE],backup[CF_BUFSIZE];
  FILE *fp;
  mode_t mask;
  char stamp[CF_BUFSIZE];
  time_t stamp_now;

#ifdef WITH_SELINUX
  int selinux_enabled=0;
  security_context_t scontext=NULL;

selinux_enabled = (is_selinux_enabled() > 0);

if (selinux_enabled)
   {

   getfilecon(file, &scontext);
   }
#endif

stamp_now = time((time_t *)NULL);

if (cfstat(file,&statbuf) == -1)
   {
   cfPS(cf_error,CF_FAIL,"stat",pp,a," !! Can no longer access file %s, which needed editing!\n",file);
   return false;
   }

strcpy(backup,file);

if (a.edits.backup == cfa_timestamp)
   {
   snprintf(stamp,CF_BUFSIZE,"_%d_%s", CFSTARTTIME,CanonifyName(cf_ctime(&stamp_now)));
   strcat(backup,stamp);
   }

strcat(backup,".cf-before-edit");

strcpy(new,file);
strcat(new,".cf-after-edit");
unlink(new);

if ((fp = fopen(new,"w")) == NULL)
   {
   cfPS(cf_error,CF_FAIL,"fopen",pp,a,"Couldn't write file %s after editing\n",new);
   return false;
   }

for (ip = liststart; ip != NULL; ip=ip->next)
   {
   fprintf(fp,"%s\n",ip->name);
   }

if (fclose(fp) == -1)
   {
   cfPS(cf_error,CF_FAIL,"fclose",pp,a,"Unable to close file while writing","fclose");
   return false;
   }

cfPS(cf_inform,CF_CHG,"",pp,a," -> Edited file %s \n",file);

if (cf_rename(file,backup) == -1)
   {
   cfPS(cf_error,CF_FAIL,"cf_rename",pp,a," !! Can't rename %s to %s - so promised edits could not be moved into place\n",file,backup);
   return false;
   }

if (a.edits.backup != cfa_nobackup)
   {
   if (ArchiveToRepository(backup,a,pp))
      {
      unlink(backup);
      }
   }
else
   {
   unlink(backup);
   }

if (cf_rename(new,file) == -1)
   {
   cfPS(cf_error,CF_FAIL,"cf_rename",pp,a," !! Can't rename %s to %s - so promised edits could not be moved into place\n",new,file);
   return false;
   }

mask = umask(0);
cf_chmod(file,statbuf.st_mode);
chown(file,statbuf.st_uid,statbuf.st_gid);
umask(mask);

#ifdef WITH_SELINUX
if (selinux_enabled)
   {

   setfilecon(file,scontext);
   }
#endif

return true;
}
