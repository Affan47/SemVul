LoadSetuid(struct Attributes a,struct Promise *pp)

{ struct Attributes b = {{0}};
  char filename[CF_BUFSIZE];

b = a;
b.edits.backup = cfa_nobackup;
b.edits.maxfilesize = 1000000;

snprintf(filename,CF_BUFSIZE,"/var/log/cfagent.%s.log",VSYSNAME.nodename);
MapName(filename);

if (!LoadFileAsItemList(&VSETUIDLIST,filename,b,pp))
   {
   CfOut(cf_verbose,"","Did not find any previous setuid log %s, creating a new one",filename);
   }
}
