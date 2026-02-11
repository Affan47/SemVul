qmonProjectOk(Widget w, XtPointer cld, XtPointer cad)
{
   lList *prjl = NULL;
   lList *alp = NULL;
   lEnumeration *what = NULL;
   Boolean status = False;
   XmString xprjname = NULL;
   StringConst prjname = NULL;
   lListElem *new_prep = NULL;
   lListElem *prep = NULL;

   DENTER(GUI_LAYER, "qmonProjectOk");


   prjl = lCreateList("PR_ADD", PR_Type);
   prep = lCreateElem(PR_Type);

   if (prjl) {
      if (qmonProjectGetAsk(prep)) {
         prjname = lGetString(prep, PR_name);


         what = lWhat("%T(ALL)", PR_Type);

         if (add_mode) {
            lAppendElem(prjl, lCopyElem(prep));
            alp = qmonAddList(SGE_PR_LIST,
                              qmonMirrorListRef(SGE_PR_LIST),
                              PR_name, &prjl, NULL, what);
         }
         else {


            qmonMirrorMultiAnswer(PROJECT_T, &alp);
            if (alp) {
               qmonMessageBox(w, alp, 0);
               lFreeList(&alp);
               DEXIT;
               return;
            }

            new_prep = lCopyElem(lGetElemStr(qmonMirrorList(SGE_PR_LIST),
                                    PR_name, prjname));
            lSwapList(new_prep, PR_acl, prep, PR_acl);
            lSwapList(new_prep, PR_xacl, prep, PR_xacl);
            lAppendElem(prjl, new_prep);
            alp = qmonModList(SGE_PR_LIST,
                              qmonMirrorListRef(SGE_PR_LIST),
                              PR_name, &prjl, NULL, what);
         }

         if (lFirst(alp) && lGetUlong(lFirst(alp), AN_status) == STATUS_OK)
            status = True;

         qmonMessageBox(w, alp, 0);

         if (status) {
            XtUnmanageChild(project_ask_layout);
            updateProjectList();
            if (add_mode) {
               XmListSelectPos(project_names, 0, True);
            }
            else {
               xprjname = XmtCreateXmString(prjname);
               XmListSelectItem(project_names, xprjname, True);
               XmStringFree(xprjname);
            }
         }
         lFreeWhat(&what);
         lFreeList(&prjl);
         lFreeElem(&prep);
         lFreeList(&alp);
      }
   }


   DEXIT;
}
