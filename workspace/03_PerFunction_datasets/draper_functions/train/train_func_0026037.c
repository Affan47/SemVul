startelm(void *userdata, int parent,
                    const char *nspace, const char *name, const char **atts)
{
    ne_propfind_handler *hdl = userdata;
    struct propstat *pstat = ne_207_get_current_propstat(hdl->parser207);
    struct prop *prop;
    int n;
    const char *lang;


    if ((parent != NE_207_STATE_PROP && parent != ELM_flatprop)
        || pstat == NULL)
        return NE_XML_DECLINE;

    if (parent == ELM_flatprop) {

        hdl->depth++;
        if (hdl->value->used < MAX_FLATPROP_LEN)
            ne_buffer_concat(hdl->value, "<", name, ">", NULL);
        return ELM_flatprop;
    }


    if (++hdl->current->counter == MAX_PROP_COUNTER) {
        ne_xml_set_error(hdl->parser, _("Response exceeds maximum property count"));
        return NE_XML_ABORT;
    }


    n = pstat->numprops;

    pstat->props = ne_realloc(pstat->props, sizeof(struct prop) * (n + 1));
    pstat->numprops = n+1;


    prop = &pstat->props[n];

    prop->pname.name = prop->name = ne_strdup(name);
    if (nspace[0] == '\0') {
	prop->pname.nspace = prop->nspace = NULL;
    } else {
	prop->pname.nspace = prop->nspace = ne_strdup(nspace);
    }
    prop->value = NULL;

    NE_DEBUG(NE_DBG_XML, "Got property #%d: {%s}%s.\n", n,
	     NSPACE(prop->nspace), prop->name);


    lang = ne_xml_get_attr(hdl->parser, atts, NULL, "xml:lang");
    if (lang != NULL) {
	prop->lang = ne_strdup(lang);
	NE_DEBUG(NE_DBG_XML, "Property language is %s\n", prop->lang);
    } else {
	prop->lang = NULL;
    }

    hdl->depth = 0;

    return ELM_flatprop;
}
