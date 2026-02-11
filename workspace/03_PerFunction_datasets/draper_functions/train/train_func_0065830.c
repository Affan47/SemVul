qmonARResourceRemoveResource(Widget w, XtPointer cld, XtPointer cad)
{
   XmIconListCallbackStruct *cbs = (XmIconListCallbackStruct*) cad;
   lListElem *dep = NULL;
   Boolean found = False;
   StringConst name, value;

   DENTER(GUI_LAYER, "qmonARSubRemoveResource");

   if (arresource_resources) {
      for_each (dep, arresource_resources) {
         name = lGetString(dep, CE_name);
         value = lGetString(dep, CE_stringval);
         if (cbs->element->string[0] && name &&
            !strcmp(cbs->element->string[0], name) &&
            cbs->element->string[2] && value &&
            !strcmp(cbs->element->string[2], value) ) {
               found = True;
               break;
         }
      }

      if (found) {
         lRemoveElem(arresource_resources, &dep);
         if (lGetNumberOfElem(arresource_resources) == 0)
            lFreeList(&arresource_resources);
         qmonRequestDraw(arresource_sr, arresource_resources, 1);
      }
   }

   DEXIT;
}
