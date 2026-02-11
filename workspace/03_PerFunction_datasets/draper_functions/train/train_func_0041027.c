ViewObjDump(GtkWidget *W,gpointer Unused)
{
FILE *Fp;
gchar DumpFName[MAX_FNAME],Out[MAX_FSIZE],Line[256];

strcpy(DumpFName,FileName); DumpFName[strlen(FileName)-2]='\0'; strcat(DumpFName,".lst");
if (!(Fp=fopen(DumpFName,"r")))
   {  Attention("ERROR: Dump file not found!\nPlease Compile or Assemble first",FALSE); return; }
sprintf(Out,"Displaying file %s\n",DumpFName);
while (TRUE)
   {
   if (strlen(Out)>(MAX_FSIZE-250)) { strcat(Out,"...file too big, view truncated"); break; }
   if (!fgets(Line,255,Fp)) break;
   strcat(Out,Line);
   }
fclose(Fp);
Attention(Out,TRUE);
}
