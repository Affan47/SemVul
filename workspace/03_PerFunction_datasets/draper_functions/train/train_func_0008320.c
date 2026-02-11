_introspect_interface_append(Eina_Strbuf *buf, E_DBus_Interface *iface, int level)
{
  E_DBus_Method *m;
  E_DBus_Signal *s;
  Eina_List *l;

  _introspect_indent_append(buf, level);
  eina_strbuf_append(buf, "<interface name=\"");
  eina_strbuf_append(buf, iface->name);
  eina_strbuf_append(buf, "\">\n");
  level++;

  DBG("introspect iface: %s", iface->name);
  EINA_LIST_FOREACH(iface->methods, l, m)
    _introspect_method_append(buf, m, level);
  EINA_LIST_FOREACH(iface->signals, l, s)
    _introspect_signal_append(buf, s, level);

  level--;
  _introspect_indent_append(buf, level);
  eina_strbuf_append(buf, "</interface>\n");
}
