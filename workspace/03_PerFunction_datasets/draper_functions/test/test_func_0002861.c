oc_SwigType_del_reference(SwigType *t) {
    char *c = Char(t);
    if (strncmp(c, "q(", 2) == 0) {
      Delete(SwigType_pop(t));
      c = Char(t);
    }
    if (strncmp(c, "r.", 2)) {
      printf("Fatal error. SwigType_del_pointer applied to non-pointer.\n");
      abort();
    }
    Replace(t, "r.", "", DOH_REPLACE_ANY | DOH_REPLACE_FIRST);
  }
