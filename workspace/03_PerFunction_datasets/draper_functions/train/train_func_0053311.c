ReportSoftware(struct CfPackageManager *list)

{ FILE *fout;
  struct CfPackageManager *mp = NULL;
  struct CfPackageItem *pi;
  char name[CF_BUFSIZE];

GetSoftwareCacheFilename(name);

if ((fout = fopen(name,"w")) == NULL)
   {
   CfOut(cf_error,"fopen","Cannot open the destination file %s",name);
   return;
   }

for (mp = list; mp != NULL; mp = mp->next)
   {
   for (pi = mp->pack_list; pi != NULL; pi=pi->next)
      {
      fprintf(fout,"%s,",CanonifyChar(pi->name,','));
      fprintf(fout,"%s,",CanonifyChar(pi->version,','));
      fprintf(fout,"%s,%s\n",pi->arch,ReadLastNode(GetArg0(mp->manager)));
      }
   }

fclose(fout);
}
