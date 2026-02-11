jshSaveToFlash() {
  FILE *f = fopen("espruino.state","wb");
  if (f) {
    unsigned int jsVarCount = jsvGetMemoryTotal();
    jsiConsolePrintf("\nSaving %d bytes...", jsVarCount*sizeof(JsVar));
    JsVarRef i;

    for (i=1;i<=jsVarCount;i++) {
      fwrite(_jsvGetAddressOf(i),1,sizeof(JsVar),f);
    }
    fclose(f);
    jsiConsolePrint("\nDone!\n>");
  } else {
    jsiConsolePrint("\nFile Open Failed... \n>");
  }
}
