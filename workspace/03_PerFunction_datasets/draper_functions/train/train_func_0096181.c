qmonJobHandleEnterLeave(
Widget w,
XtPointer cld,
XEvent *ev,
Boolean *ctd
) {


   char line[BUFSIZ];
   static int prev_row = -1;
   int row, col;
   String str;
   int job_nr;
   lListElem *jep;

   DENTER(GUI_LAYER, "qmonJobHandleEnterLeave");

   switch (ev->type) {
      case MotionNotify:
         if (qmonBrowserObjectEnabled(BROWSE_JOB)) {


            if (XbaeMatrixGetEventRowColumn(w, ev, &row, &col)) {
               if ( row != prev_row ) {
                  prev_row = row;

                  str = XbaeMatrixGetCell(w, row, 0);
                  if (str && *str != '\0') {
                     job_nr = atoi(str);
                     jep = job_list_locate(qmonMirrorList(SGE_JB_LIST),
                                          (u_long32)job_nr);
                     if (jep) {
                        dstring job_info = DSTRING_INIT;
                        sprintf(line, "+++++++++++++++++++++++++++++++++++++++++++\n");
                        qmonBrowserShow(line);
                        qmonJobShowBrowserInfo(&job_info, jep);
                        qmonBrowserShow(sge_dstring_get_string(&job_info));
                        sge_dstring_free(&job_info);
                     }
                  }
               }
            }
         }
         break;
   }
   DEXIT;
}
