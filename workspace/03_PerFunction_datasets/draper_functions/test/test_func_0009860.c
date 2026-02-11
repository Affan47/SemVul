inf_session_set_xml_user_props_impl(InfSession* session,
                                    const GParameter* params,
                                    guint n_params,
                                    xmlNodePtr xml)
{
  guint i;
  gchar id_buf[16];
  const gchar* name;
  InfUserStatus status;
#if 0
  InfXmlConnection* conn;
  gchar* remote_address;
#endif

  for(i = 0; i < n_params; ++ i)
  {
    if(strcmp(params[i].name, "id") == 0)
    {
      sprintf(id_buf, "%u", g_value_get_uint(&params[i].value));
      xmlNewProp(xml, (const xmlChar*)"id", (const xmlChar*)id_buf);
    }
    else if(strcmp(params[i].name, "name") == 0)
    {
      name = g_value_get_string(&params[i].value);
      xmlNewProp(xml, (const xmlChar*)"name", (const xmlChar*)name);
    }
    else if(strcmp(params[i].name, "status") == 0)
    {
      status = g_value_get_enum(&params[i].value);

      inf_xml_util_set_attribute(
        xml,
        "status",
        inf_user_status_to_string(status)
      );
    }


  }
}
