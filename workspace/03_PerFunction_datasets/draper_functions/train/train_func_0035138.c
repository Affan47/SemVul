AllocateEntryNode(
  void *theEnv,
  FILE *fp,
  char *file,
  char *str,
  int line_ct)
  {
   struct entries *enode;
   char bmarker[BDLEN+1],
        t_code[2];


   enode = (struct entries *) gm2(theEnv,(int) sizeof(struct entries));
   if (sscanf(str,BFORMAT,
              &enode->level,t_code,bmarker,enode->name) != 4)
     {
      rm(theEnv,(void *) enode,(int) sizeof(struct entries));
      GenClose(theEnv,fp);
      TextLookupToss(theEnv,file);

      PrintErrorID(theEnv,"TEXTPRO",5,FALSE);
      EnvPrintRouter(theEnv,WERROR,"Line ");
      PrintLongInteger(theEnv,WERROR,line_ct);
      EnvPrintRouter(theEnv,WERROR," : Invalid delimeter string.\n");

      return(NULL);
     }
   if (t_code[0] == 'M')
     enode->type = MENU;
   else if (t_code[0] == 'I')
     enode->type = INFO;
   else
     {
      rm(theEnv,(void *) enode,(int) sizeof(struct entries));
      GenClose(theEnv,fp);
      TextLookupToss(theEnv,file);

      PrintErrorID(theEnv,"TEXTPRO",6,FALSE);
      EnvPrintRouter(theEnv,WERROR,"Line ");
      PrintLongInteger(theEnv,WERROR,line_ct);
      EnvPrintRouter(theEnv,WERROR," : Invalid entry type.\n");

      return(NULL);
     }
   if (strcmp(bmarker,BDELIM) != 0)
     {
      rm(theEnv,(void *) enode,(int) sizeof(struct entries));
      GenClose(theEnv,fp);
      TextLookupToss(theEnv,file);

      PrintErrorID(theEnv,"TEXTPRO",5,FALSE);
      EnvPrintRouter(theEnv,WERROR,"Line ");
      PrintLongInteger(theEnv,WERROR,line_ct);
      EnvPrintRouter(theEnv,WERROR," : Invalid delimeter string.\n");

      return(NULL);
     }


   ungetc(getc(fp),fp);
   enode->offset = ftell(fp);

   enode->parent = NULL;
   enode->child  = NULL;
   enode->next = NULL;
   upper(enode->name);

   return(enode);
  }
