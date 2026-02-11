value(void)const
{

  if (_brh) {
    return _brh->probe_num(_what);
  }else{
    return probe_node();
  }
}
