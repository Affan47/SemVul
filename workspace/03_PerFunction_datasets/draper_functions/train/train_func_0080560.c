Book (Ekiga::ServiceCore &_core) :
  core(_core), doc()
{
  xmlNodePtr root = NULL;

  gchar *c_raw = gm_conf_get_string (KEY);

  if (c_raw != NULL) {

    const std::string raw = c_raw;

    doc = boost::shared_ptr<xmlDoc> (xmlRecoverMemory (raw.c_str (), raw.length ()), xmlFreeDoc);
    if ( !doc)
      doc = boost::shared_ptr<xmlDoc> (xmlNewDoc (BAD_CAST "1.0"), xmlFreeDoc);

    root = xmlDocGetRootElement (doc.get ());
    if (root == NULL) {

      root = xmlNewDocNode (doc.get (), NULL, BAD_CAST "list", NULL);
      xmlDocSetRootElement (doc.get (), root);
    }

    for (xmlNodePtr child = root->children;
	 child != NULL;
	 child = child->next)
      if (child->type == XML_ELEMENT_NODE
	  && child->name != NULL
	  && xmlStrEqual (BAD_CAST ("entry"), child->name))
        add (child);

    g_free (c_raw);
  } else {

    doc = boost::shared_ptr<xmlDoc> (xmlNewDoc (BAD_CAST "1.0"), xmlFreeDoc);
    root = xmlNewDocNode (doc.get (), NULL, BAD_CAST "list", NULL);
    xmlDocSetRootElement (doc.get (), root);
  }

  boost::shared_ptr<Ekiga::CallCore> call_core = core.get<Ekiga::CallCore> ("call-core");

  call_core->missed_call.connect (boost::bind (&History::Book::on_missed_call, this, _1, _2));
  call_core->cleared_call.connect (boost::bind (&History::Book::on_cleared_call, this, _1, _2, _3));

  enforce_size_limit ();
}
