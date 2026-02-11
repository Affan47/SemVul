HandleLValue(char *id)

{
Debug1("HandleLVALUE(%s) in action %s\n",id,ACTIONTEXT[ACTION]);

 switch(ACTION)
    {
    case control:

        if ((CONTROLVAR = ScanVariable(id)) != nonexistentvar)
           {
           strcpy(CURRENTITEM,id);
           return;
           }
        else
           {
           if (IsDefinedClass(CLASSBUFF))
              {
              RecordMacroId(id);
              }
           return;
           }
        break;

    case groups:
        { int count = 1;
        char *cid = id;

        while (*cid != '\0')
           {
           if (*cid++ == '.')
              {
              count++;
              }
           }

        if (strcmp(id,CF_ANYCLASS) == 0)
           {
           yyerror("Reserved class <any>");
           }

        if (count > 1)
           {
           yyerror("Group with compound identifier");
           FatalError("Dots [.] not allowed in group identifiers");
           }

        if (IsHardClass(id))
           {
           yyerror("Reserved class name (choose a different name)");
           }

        strcpy(GROUPBUFF,id);
        }

    break;

    }
}
