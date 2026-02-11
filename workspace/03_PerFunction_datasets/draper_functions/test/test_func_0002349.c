MoveObstruction(char *from,struct Attributes attr,struct Promise *pp)

{ struct stat sb;
  char stamp[CF_BUFSIZE],saved[CF_BUFSIZE];
  time_t now_stamp = time((time_t *)NULL);

if (lstat(from,&sb) == 0)
   {
   if (!attr.move_obstructions)
      {
      cfPS(cf_verbose,CF_FAIL,"",pp,attr," !! Object %s exists and is obstructing our promise\n",from);
      return false;
      }

   if (!S_ISDIR(sb.st_mode))
      {
      if (DONTDO)
         {
         return false;
         }

      saved[0] = '\0';
      strcpy(saved,from);

      if (attr.copy.backup == cfa_timestamp || attr.edits.backup == cfa_timestamp)
         {
         sprintf(stamp, "_%d_%s",CFSTARTTIME,CanonifyName(cf_ctime(&now_stamp)));
         strcat(saved,stamp);
         }

      strcat(saved,CF_SAVED);

      cfPS(cf_verbose,CF_CHG,"",pp,attr," -> Moving file object %s to %s\n",from,saved);

      if (cf_rename(from,saved) == -1)
         {
         cfPS(cf_error,CF_FAIL,"cf_rename",pp,attr," !! Can't rename %s to %s\n",from,saved);
         return false;
         }

      if (ArchiveToRepository(saved,attr,pp))
         {
         unlink(saved);
         }

      return true;
      }

   if (S_ISDIR(sb.st_mode))
      {
      cfPS(cf_verbose,CF_CHG,"",pp,attr," -> Moving directory %s to %s%s\n",from,from,CF_SAVED);

      if (DONTDO)
         {
         return false;
         }

      saved[0] = '\0';
      strcpy(saved,from);

      sprintf(stamp, "_%d_%s", CFSTARTTIME, CanonifyName(cf_ctime(&now_stamp)));
      strcat(saved,stamp);
      strcat(saved,CF_SAVED);
      strcat(saved,".dir");

      if (cfstat(saved,&sb) != -1)
         {
         cfPS(cf_error,CF_FAIL,"",pp,attr," !! Couldn't save directory %s, since %s exists already\n",from,saved);
         CfOut(cf_error,"","Unable to force link to existing directory %s\n",from);
         return false;
         }

      if (cf_rename(from,saved) == -1)
         {
         cfPS(cf_error,CF_FAIL,"cf_rename",pp,attr,"Can't rename %s to %s\n",from,saved);
         return false;
         }
      }
   }

return true;
}
