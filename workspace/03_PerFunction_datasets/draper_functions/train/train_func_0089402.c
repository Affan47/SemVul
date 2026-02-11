simple_action(Packet *p)
{
  IPAddress ipa;

  if(_addrs && _max > 0){
    ipa = _addrs[random() % _max];
  } else {
    ipa = pick();
  }

  p->set_dst_ip_anno(ipa);

  return p;
}
