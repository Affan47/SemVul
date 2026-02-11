lookup_xid (object dpy, XID xid) {
  if (xid == 0) {
    VALUES1(NIL);
    return nullobj;
  } else {
    object ht = display_hash_table(dpy);
    value1 = gethash(XID_to_object_old(xid),ht,false);
    if (!eq(value1,nullobj)) {
      mv_count = 1;
      return nullobj;
    } else
      return ht;
  }
}
