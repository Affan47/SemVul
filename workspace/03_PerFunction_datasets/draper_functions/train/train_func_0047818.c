xmlrc_parse_apwal_pref(xmlDocPtr doc, xmlNodePtr cur)
{
  apwal_pref_t *apwal_pref;
  gint      timeout = 1000;
  gint      exit_at_app_launch = FALSE;
  gboolean  activate_tooltips = TRUE;
  gboolean  iconsel_in_a_separate_window = TRUE;
  gboolean  iconsel_modal = FALSE;
  char     *buf;

  cur = cur->xmlChildrenNode;
  while (cur != NULL)
  {
    if (!xmlStrcmp(cur->name, (const xmlChar *)"timeout"))
    { buf = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
      timeout = strtol(buf, (char **)NULL, 10);
      g_free(buf);
    } else if (!xmlStrcmp(cur->name, (const xmlChar *)"exit_at_app_launch"))
    { buf = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
      exit_at_app_launch = strtol(buf, (char **)NULL, 10);
      g_free(buf);
    }
    else if (!xmlStrcmp(cur->name, (const xmlChar *)"activate_tooltips"))
    { buf = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
      activate_tooltips = strtol(buf, (char **)NULL, 10);
      g_free(buf);
    }
    else if (!xmlStrcmp(cur->name,
                        (const xmlChar *)"iconsel_in_a_separate_window"))
    { buf = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
      iconsel_in_a_separate_window = strtol(buf, (char **)NULL, 10);
      g_free(buf);
    }
    else if (!xmlStrcmp(cur->name, (const xmlChar *)"iconsel_modal"))
    { buf = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
      iconsel_modal = strtol(buf, (char **)NULL, 10);
      g_free(buf);
    }
    else
      ERR("cur->name:%s unknown", cur->name);

    cur = cur->next;
  }

  apwal_pref = apwal_pref_new(timeout, exit_at_app_launch, activate_tooltips,
                              iconsel_in_a_separate_window, iconsel_modal);
  return apwal_pref;
}
