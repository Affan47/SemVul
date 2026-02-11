_dxf_getline(struct parse_state *ps)
{
   char str[MAX_DSTR];
   char *line = ps->line;
   char *current = ps->current;
   int n=0;


   if ((fgets(str,MAX_DSTR,ps->fp))==NULL){
     DXSetError(ERROR_DATA_INVALID,"#10898",ps->filename);
     return ERROR;
   }
   ps->lineno++;
   strcpy(line,str);
   while ((int)strlen(str)>MAX_DSTR-2){
      if ((fgets(str,MAX_DSTR,ps->fp))==NULL){
        DXSetError(ERROR_DATA_INVALID,"#10898",ps->filename);
        return ERROR;
      }
      n++;
      line = (char *)DXReAllocate(line,(unsigned int)strlen(str)+n*MAX_DSTR);
      strcat(line,str);
   }
   if ( strlen(line) >= 2 && line[strlen(line)-2] == '\r')
     line[strlen(line)-2] = '\n';
   current = line;
   ps->current = current;
   ps->line = line;

   return OK;
}
