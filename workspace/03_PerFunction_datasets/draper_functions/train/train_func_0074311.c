DetachActivation(
  void *theEnv,
  void *vTheActivation)
  {
   struct defruleModule *theModuleItem;
   struct activation *theActivation = (struct activation *) vTheActivation;


   if (theActivation == NULL) SystemError(theEnv,"AGENDA",1);


   theModuleItem = (struct defruleModule *) theActivation->theRule->header.whichModule;


   if (theActivation == theModuleItem->agenda)
     { theModuleItem->agenda = theActivation->next; }


   if (theActivation->prev != NULL)
     { theActivation->prev->next = theActivation->next; }


   if (theActivation->next != NULL)
     { theActivation->next->prev = theActivation->prev; }


   theActivation->prev = NULL;
   theActivation->next = NULL;


   AgendaData(theEnv)->AgendaChanged = TRUE;

   return(TRUE);
  }
