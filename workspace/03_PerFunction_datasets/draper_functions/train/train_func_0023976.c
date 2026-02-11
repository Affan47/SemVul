qmonFOTCullToMatrix(
Widget matrix,
lList *lp,
int nm0,
int nm1
) {
   lListElem *ep;
   StringConst name;
   u_long32 tickets;
   char buf[128];
   char buf2[128];
   int row;
   int max_rows;

   DENTER(GUI_LAYER, "qmonFOTCullToMatrix");


   XtVaSetValues(matrix, XmNcells, NULL, NULL);
   if (!lp) {
      DEXIT;
      return;
   }

   max_rows = XbaeMatrixNumRows(matrix);

   for (ep = lFirst(lp), row = 0; ep; ep = lNext(ep), row++) {
      if (nm0 == JB_job_number) {
         sprintf(buf2, "%d", (int)lGetUlong(ep, nm0));
         name = buf2;
      }
      else
         name = lGetString(ep, nm0);
      tickets = lGetUlong(ep, nm1);
      sprintf(buf, sge_u32, tickets);
      if (row == max_rows-1) {
         XbaeMatrixAddRows(matrix,
                           max_rows-1,
                           NULL,
                           NULL,
                           NULL,
                           1);
         max_rows++;
      }

      XbaeMatrixSetCell(matrix, row, 0, name ? (String) name : "");
      XbaeMatrixSetCell(matrix, row, 1, buf);
   }

   DEXIT;
}
