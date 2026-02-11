configure(Vector<String> &conf, ErrorHandler *errh)
{
    String name;
    if (cp_va_kparse(conf, this, errh, "LOCK", cpkP+cpkM, cpString, &name, cpEnd)<0)
	return -1;
    for (int i = 0; i < router()->nelements(); i++) {
	if (SpinlockInfo *si =
	    (SpinlockInfo *)(router()->element(i)->cast("SpinlockInfo"))) {
	    _lock = si->query(name, Element::name());
	    if (!_lock)
		return errh->error("cannot locate spinlock %s",name.c_str());
	    break;
	}
    }
    return 0;
}
