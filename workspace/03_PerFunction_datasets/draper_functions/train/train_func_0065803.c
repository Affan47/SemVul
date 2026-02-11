PrintDoubleOpti(
lListElem *ep,
lListElem *jat,
lList *eleml,
int nm
) {
   char buf[BUFSIZ];
   String str;

   DENTER(GUI_LAYER, "PrintDoubleOpti");

#define OPTI_PRINT8(value) \
   if (value > 99999999 ) \
      sprintf(buf, "%8.3g ", value); \
   else  \
      sprintf(buf, "%8.0f ", value)

   OPTI_PRINT8(lGetDouble(ep, nm));
   str = XtNewString(buf);

#undef OPTI_PRINT8

   DEXIT;
   return str;
}
