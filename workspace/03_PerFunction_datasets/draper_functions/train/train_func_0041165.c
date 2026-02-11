BsaveStorageObjects(
  void *theEnv,
  FILE *fp)
  {
   UNLN space;

   if ((ObjectBinaryData(theEnv)->ClassCount == 0L) && (ObjectBinaryData(theEnv)->HandlerCount == 0L))
     {
      space = 0L;
      GenWrite((void *) &space,(UNLN) sizeof(long),fp);
      return;
     }
   space = sizeof(long) * 9;
   GenWrite((void *) &space,(UNLN) sizeof(long),fp);
   GenWrite((void *) &ObjectBinaryData(theEnv)->ModuleCount,(UNLN) sizeof(long),fp);
   GenWrite((void *) &ObjectBinaryData(theEnv)->ClassCount,(UNLN) sizeof(long),fp);
   GenWrite((void *) &ObjectBinaryData(theEnv)->LinkCount,(UNLN) sizeof(long),fp);
   GenWrite((void *) &ObjectBinaryData(theEnv)->SlotNameCount,(UNLN) sizeof(long),fp);
   GenWrite((void *) &ObjectBinaryData(theEnv)->SlotCount,(UNLN) sizeof(long),fp);
   GenWrite((void *) &ObjectBinaryData(theEnv)->TemplateSlotCount,(UNLN) sizeof(long),fp);
   GenWrite((void *) &ObjectBinaryData(theEnv)->SlotNameMapCount,(UNLN) sizeof(long),fp);
   GenWrite((void *) &ObjectBinaryData(theEnv)->HandlerCount,(UNLN) sizeof(long),fp);
   space = (UNLN) DefclassData(theEnv)->MaxClassID;
   GenWrite((void *) &space,(UNLN) sizeof(long),fp);
  }
