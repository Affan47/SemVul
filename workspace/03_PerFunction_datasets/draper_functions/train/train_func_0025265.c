PrintState(
lListElem *ep,
int nm
) {
   char buf[128] = "";
   String str;

   DENTER(GUI_LAYER, "PrintState");


   ar_get_state_string(buf, sizeof(buf), lGetUlong(ep, AR_state));

   str = XtNewString(buf);

   DEXIT;
   return str;
}
