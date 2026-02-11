babel_ifiction_lint(char *md)
{
 struct IFiction_Info ii;
 int i=1;
 ii.wmode=1;
 isok=1;
 strcpy(ii.ifid,"UNKNOWN");
 ifiction_parse(md,examine_tag,&ii,verify_eh,&i);
 if (isok) printf("%s conforms to iFiction style guidelines\n",ii.ifid);
}
