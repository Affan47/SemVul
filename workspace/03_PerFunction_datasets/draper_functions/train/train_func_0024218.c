prefix_to_ports(const GUTF8String &prefix)
{
  GPList<DjVuPort> list;
  {
    int length=prefix.length();
    if (length)
    {
      GCriticalSectionLock lock(&map_lock);
      for(GPosition pos=a2p_map;pos;++pos)
        if (!prefix.cmp(a2p_map.key(pos), length))
        {
          DjVuPort * port=(DjVuPort *) a2p_map[pos];
          GP<DjVuPort> gp_port=is_port_alive(port);
          if (gp_port) list.append(gp_port);
        }
    }
  }
  return list;
}
