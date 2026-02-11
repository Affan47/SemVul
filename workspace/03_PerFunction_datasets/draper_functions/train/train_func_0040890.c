getAllClassMixinsOf(Tcl_Interp *interp, Tcl_HashTable *destTable, XOTclClass *startCl,
		    int isMixin,
                    int appendResult, char *pattern, XOTclObject *matchObject) {
  int rc = 0, new = 0;
  XOTclClass *cl;
  XOTclClasses *sc;


  if (isMixin) {
    rc = addToResultSet(interp, destTable, &startCl->object, &new, appendResult, pattern, matchObject);
    if (rc == 1) {return rc;}


    for (sc = startCl->sub; sc; sc = sc->next) {
      rc = getAllClassMixinsOf(interp, destTable, sc->cl, isMixin, appendResult, pattern, matchObject);
      if (rc) {return rc;}
    }
  }


  if (startCl->opt) {
    XOTclCmdList *m;

    for (m = startCl->opt->isClassMixinOf; m; m = m->next) {


      assert(Tcl_Command_cmdEpoch(m->cmdPtr) == 0);

      cl = XOTclGetClassFromCmdPtr(m->cmdPtr);
      assert(cl);

      rc = addToResultSet(interp, destTable, &cl->object, &new, appendResult, pattern, matchObject);
      if (rc == 1) {return rc;}
      if (new) {
        rc = getAllClassMixinsOf(interp, destTable, cl, 1, appendResult, pattern, matchObject);
        if (rc) {return rc;}
      }
    }
  }

  return rc;
}
