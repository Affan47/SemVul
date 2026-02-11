qmonPEOk(Widget w, XtPointer cld, XtPointer cad)
{
   lList *pel = NULL;
   lList *alp;
   lEnumeration *what;
   Boolean status = False;
   XmString xpename = NULL;
   StringConst pename = NULL;

   DENTER(GUI_LAYER, "qmonPEOk");


   pel = lCreateElemList("PE_ADD", PE_Type, 1);

   if (pel) {
      if (qmonPEGetAsk(lFirst(pel))) {

         pename = (StringConst)lGetString(lFirst(pel), PE_name);


         what = lWhat("%T(ALL)", PE_Type);

         if (add_mode) {
            alp = qmonAddList(SGE_PE_LIST, qmonMirrorListRef(SGE_PE_LIST),
                              PE_name, &pel, NULL, what);
         }
         else {
            alp = qmonModList(SGE_PE_LIST, qmonMirrorListRef(SGE_PE_LIST),
                              PE_name, &pel, NULL, what);
         }

         if (lFirst(alp) && lGetUlong(lFirst(alp), AN_status) == STATUS_OK)
            status = True;

         qmonMessageBox(w, alp, 0);

         if (status) {
            XtUnmanageChild(pe_ask_layout);
            updatePeList();


            xpename = XmtCreateXmString(pename);
            XmListSelectItem(pe_names, xpename, True);
            XmStringFree(xpename);
         }
         lFreeWhat(&what);
         lFreeList(&alp);
      }
      lFreeList(&pel);
   }
   DEXIT;
}
