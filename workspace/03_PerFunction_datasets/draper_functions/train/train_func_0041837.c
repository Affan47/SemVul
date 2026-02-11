BloadStorage(
  void *theEnv)
  {
   unsigned long int space;


   GenReadBinary(theEnv,&space,(unsigned long) sizeof(unsigned long int));
   GenReadBinary(theEnv,&DeftemplateBinaryData(theEnv)->NumberOfDeftemplates,(unsigned long) sizeof(long int));
   GenReadBinary(theEnv,&DeftemplateBinaryData(theEnv)->NumberOfTemplateSlots,(unsigned long) sizeof(long int));
   GenReadBinary(theEnv,&DeftemplateBinaryData(theEnv)->NumberOfTemplateModules,(unsigned long) sizeof(long int));


   if (DeftemplateBinaryData(theEnv)->NumberOfTemplateModules == 0)
     {
      DeftemplateBinaryData(theEnv)->DeftemplateArray = NULL;
      DeftemplateBinaryData(theEnv)->SlotArray = NULL;
      DeftemplateBinaryData(theEnv)->ModuleArray = NULL;
      return;
     }

   space = DeftemplateBinaryData(theEnv)->NumberOfTemplateModules * sizeof(struct deftemplateModule);
   DeftemplateBinaryData(theEnv)->ModuleArray = (struct deftemplateModule *) genlongalloc(theEnv,space);


   if (DeftemplateBinaryData(theEnv)->NumberOfDeftemplates == 0)
     {
      DeftemplateBinaryData(theEnv)->DeftemplateArray = NULL;
      DeftemplateBinaryData(theEnv)->SlotArray = NULL;
      return;
     }

   space = DeftemplateBinaryData(theEnv)->NumberOfDeftemplates * sizeof(struct deftemplate);
   DeftemplateBinaryData(theEnv)->DeftemplateArray = (struct deftemplate *) genlongalloc(theEnv,space);


   if (DeftemplateBinaryData(theEnv)->NumberOfTemplateSlots == 0)
     {
      DeftemplateBinaryData(theEnv)->SlotArray = NULL;
      return;
     }

   space =  DeftemplateBinaryData(theEnv)->NumberOfTemplateSlots * sizeof(struct templateSlot);
   DeftemplateBinaryData(theEnv)->SlotArray = (struct templateSlot *) genlongalloc(theEnv,space);
  }
