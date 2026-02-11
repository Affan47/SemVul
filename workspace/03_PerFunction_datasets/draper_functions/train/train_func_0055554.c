AskForNewHelpTopic(
  void *theEnv,
  struct topics *old_list,
  char **menu)
  {
   int theIndex, cnt;
   struct topics *tmain,
                 *tnode,
                 *tptr;
   char list[256],
        name[NAMESIZE];


   EnvPrintRouter(theEnv,"whelp",*menu);
   EnvPrintRouter(theEnv,"whelp"," Topic? ");
   RouterData(theEnv)->CommandBufferInputCount = 0;
   for ( theIndex = 0;
         ((list[theIndex] = (char) EnvGetcRouter(theEnv,"whelp")) != LNFEED) && (theIndex < 254);
         theIndex++ , RouterData(theEnv)->CommandBufferInputCount++)
       {
        if (EvaluationData(theEnv)->HaltExecution)
          break;
        if (list[theIndex] == TAB)
          list[theIndex] = BLANK;
        else if ((list[theIndex] == '\b') && (theIndex != 0))
          {
           theIndex -= 2;
           RouterData(theEnv)->CommandBufferInputCount -= 2;
          }
       }
#if VAX_VMS
   EnvPrintRouter(theEnv,"whelp","\n");
#endif

   RouterData(theEnv)->CommandBufferInputCount = -1;
   if (EvaluationData(theEnv)->HaltExecution)
     {
      EnvPrintRouter(theEnv,"whelp","\n");
      old_list->end_list = old_list;
      return(old_list);
     }
   list[theIndex] = BLANK;
   list[theIndex+1] = NULLCHAR;


   tmain = old_list;
   theIndex = 0; cnt = 0;
   while (list[theIndex] != NULLCHAR)
     {
      if ((list[theIndex] != BLANK) && (cnt < NAMESIZE))
        name[cnt++] = list[theIndex++];
      else if (cnt > 0)
        {
         while ((list[theIndex] != BLANK) && (list[theIndex] != NULLCHAR))
           theIndex++;
         name[cnt] = NULLCHAR;
         cnt = 0;


         if (old_list != NULL)
           {
            strcpy(old_list->name,name);
            old_list = old_list->next;
           }
         else
           {
            tnode = (struct topics *) gm2(theEnv,(int) sizeof(struct topics));
            strcpy(tnode->name,name);
            tnode->next = NULL;
            tnode->end_list = NULL;
            if (tmain == NULL)
              tmain = tnode;
            else
              {
               tptr = tmain;
               while (tptr->next != NULL)
                 tptr = tptr->next;
               tptr->next = tnode;
              }
           }
        }
      else
        theIndex++;
     }


  tmain->end_list = old_list;
  return(tmain);
 }
