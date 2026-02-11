alarm(void)
{
  _out.setfloatwidth(OPT::numdgt, OPT::numdgt+6);
  for (PROBELIST::const_iterator
	 p=alarmlist().begin();  p!=alarmlist().end();  ++p) {
    if (!p->in_range()) {
      _out << p->label() << '=' << p->value() << '\n';
    }else{
    }
  }
}
