GWEN_InheritData_free(GWEN_INHERITDATA *d) {
  if (d) {
    if (d->freeDataFn)
      d->freeDataFn(d->baseData, d->data);
    free(d->typeName);
    GWEN_LIST_FINI(GWEN_INHERITDATA, d);
    GWEN_FREE_OBJECT(d);
  }
}
