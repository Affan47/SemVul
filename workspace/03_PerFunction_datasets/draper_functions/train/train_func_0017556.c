FilterStackPop(XOTclObject *obj) {
  register XOTclFilterStack *h = obj->filterStack;
  obj->filterStack = h->next;


  DECR_REF_COUNT(h->calledProc);
  FREE(XOTclFilterStack, h);
}
