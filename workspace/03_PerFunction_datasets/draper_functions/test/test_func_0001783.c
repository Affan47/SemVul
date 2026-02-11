node_id_xml(const node_id_t *id)
{
  gchar *msg;
  gchar *msgb;
  gchar *xml;
  g_assert(id);
  switch (id->node_type)
    {
    case APEMODE_DEFAULT:
      msg = g_strdup_printf(" ");
      break;
    case LINK6:
      msg = xmltag("link", "%s", ether_to_str(id->addr.eth));
      break;
    case IP:
      msg = xmltag(type_to_str (&id->addr.ip), "%s", address_to_str (&id->addr.ip));
      break;
    case TCP:
      xml = xmltag(type_to_str (&id->addr.tcp4.host),
                   "%s",
                   address_to_str (&id->addr.tcp4.host));
      msgb = xmltag("port", "%u", id->addr.tcp4.port);
      msg = g_strdup_printf("%s %s", xml, msgb);
      g_free(xml);
      g_free(msgb);
      break;
    default:
      msg = xmltag("unknown","node_id_type %d unknown", (int)(id->node_type));
      break;
    }
  xml = xmltag("id", "\n%s", msg);
  g_free(msg);

  return xml;
}
