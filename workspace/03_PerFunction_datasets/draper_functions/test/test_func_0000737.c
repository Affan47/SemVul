qmonDeleteJobForMatrix(
Widget w,
Widget matrix,
lList **local
) {
   int i;
   int rows;
   lList *jl = NULL;
   lList *sl = NULL;
   lListElem *jep = NULL;
   lList *alp = NULL;
   char *str;
   int force;
   static lList *user_list = NULL;

   DENTER(GUI_LAYER, "qmonDeleteJobForMatrix");


   force = XmToggleButtonGetState(force_toggle);


   rows = XbaeMatrixNumRows(matrix);
   for (i=0; i<rows; i++) {

      if (XbaeMatrixIsRowSelected(matrix, i)) {
         str = XbaeMatrixGetCell(matrix, i, 0);
         if ( str && *str != '\0' ) {
            DPRINTF(("JobTask(s) to delete: %s\n", str));

            if (sge_parse_jobtasks(&jl, &jep, str, &alp, false, NULL) == -1) {
               qmonMessageBox(w, alp, 0);
               DEXIT;
               return False;
            }
            lSetUlong(jep, ID_force, force);
            lSetList(jep, ID_user_list, lCopyList("", user_list));
         }
      }
   }

   if (jl) {


      int job_max = 100;
      int num_jobs = lGetNumberOfElem(jl);
      int count = 0;

      while (num_jobs) {
         int j=0;
         lListElem *ep, *next;
         count++;
         for (ep = lFirst(jl); ep; ep = next, j++) {
            next=ep->next;
            if (!sl) {
               sl = lCreateList("sl", ID_Type);
            }
            ep = lDechainElem(jl, ep);
            lAppendElem(sl, ep);
            if (j==job_max) {
               break;
            }
         }
         num_jobs = lGetNumberOfElem(jl);
         alp = qmonDelList(SGE_JB_LIST, local,
                           ID_str, &sl, NULL, NULL);
         qmonMessageBox(w, alp, 0);
         lFreeList(&alp);
         lFreeList(&sl);
      }

      updateJobList();
      XbaeMatrixDeselectAll(matrix);

      lFreeList(&jl);
   }
#if 0
   else {
      qmonMessageShow(w, True, "@{There are no jobs selected !}");
      DEXIT;
      return False;
   }
#endif

   DEXIT;
   return True;
}
