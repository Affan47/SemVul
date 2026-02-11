PrintString(
lListElem *ep,
lListElem *jat,
lList *eleml,
int nm
) {

   String str;
   StringConst temp;

   DENTER(GUI_LAYER, "PrintString");

   temp = lGetString(ep, nm);

   str = XtNewString(temp?temp:"");

   DEXIT;
   return str;
}
