genCOPY_UP_SEG(locname, insname, newname)
char *insname;
char *locname;
char *newname;
{
phfig_list *ptnewfig;
phins_list *ptins;
phseg_list *ptseg;
long x1, x2, y1, y2;
int  found = 0;
chain_list *c = NULL;

   if (WORK_PHFIG == NULL) {
      (void)fflush(stdout);
      (void)fputs("*** genlib error ***\n", stderr);
      (void)fputs("COPY_UP_SEG impossible : missing DEF_PHFIG\n", stderr);
      EXIT(1);
   }
   ptins = getphins(WORK_PHFIG, insname);
   ptnewfig = getphfig(ptins->FIGNAME, 'A');
   locname = namealloc(checkname(locname));

   for (ptseg = ptnewfig->PHSEG; ptseg; ptseg = ptseg->NEXT) {
      if (ptseg->NAME == locname) {

         xyflat(&x1, &y1, ptseg->X1, ptseg->Y1, ptins->XINS, ptins->YINS,
                 ptnewfig->XAB1, ptnewfig->YAB1, ptnewfig->XAB2, ptnewfig->YAB2,
                 ptins->TRANSF);
         xyflat(&x2, &y2, ptseg->X2, ptseg->Y2, ptins->XINS, ptins->YINS,
                 ptnewfig->XAB1, ptnewfig->YAB1, ptnewfig->XAB2, ptnewfig->YAB2,
                 ptins->TRANSF);
         c = addchain(c, addphseg(WORK_PHFIG, ptseg->LAYER, ptseg->WIDTH,
                                  x1, y1, x2, y2, checkname(newname)));

         found = 1;
      }
   }
   if (!found) {
      (void)fflush(stdout);
      (void)fputs("*** genlib error ***\nCOPY_UP_SEG impossible :", stderr);
      (void)fprintf(stderr, " segment %s doesn't exist in instance %s\n",
                     locname, insname);
      EXIT(1);
   }

   return addptype(NULL, MBK_SEGMENT, c);
}
