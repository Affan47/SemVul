cmpTplScore (void *tpl1, void *tpl2)
  {
    double  l1, l2;

    l1 = ((topol *) tpl1)->likelihood;
    l2 = ((topol *) tpl2)->likelihood;
    return  (l1 > l2) ? -1 : ((l1 == l2) ? 0 : 1);
  }
