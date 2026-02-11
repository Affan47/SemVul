g_graphical_objs_in_net_with_attrib_get_attrib (SCM scm_netname, SCM scm_has_attribute, SCM scm_wanted_attribute)
{

    SCM list = SCM_EOL;
    NETLIST *nl_current;
    CPINLIST *pl_current;
    char *wanted_net_name;
    char *wanted_attrib;
    char *has_attrib;
    char *net_name;
    char *attrib_value=NULL;
    char *has_attrib_value = NULL;
    char *has_attrib_name = NULL;

    SCM_ASSERT(scm_is_string (scm_netname), scm_netname, SCM_ARG1,
	       "gnetlist:get-attr-of-conn-graph-objs-with-attr");

    SCM_ASSERT(scm_is_string (scm_wanted_attribute),
	       scm_wanted_attribute, SCM_ARG3,
	       "gnetlist:get-attr-of-conn-graph-objs-with-attr");

    SCM_ASSERT(scm_is_string (scm_has_attribute),
	       scm_has_attribute, SCM_ARG2,
	       "gnetlist:get-attr-of-conn-graph-objs-with-attr");

    scm_dynwind_begin (0);

    wanted_net_name = scm_to_utf8_string (scm_netname);
    if (wanted_net_name == NULL) {
	return list;
    }

    scm_dynwind_free (wanted_net_name);

    wanted_attrib = scm_to_utf8_string (scm_wanted_attribute);
    scm_dynwind_free (wanted_attrib);

    has_attrib = scm_to_utf8_string (scm_has_attribute);
    scm_dynwind_free (has_attrib);

    nl_current = graphical_netlist_head;


    while (nl_current != NULL) {
	pl_current = nl_current->cpins;
	while (pl_current != NULL) {
	    if (pl_current->net_name) {
		net_name = pl_current->net_name;
		if (strcmp(net_name, wanted_net_name) == 0) {

		  if (o_attrib_string_get_name_value (has_attrib, &has_attrib_name,
					       &has_attrib_value) != 0) {
		    attrib_value =
		      o_attrib_search_object_attribs_by_name (nl_current->object_ptr,
		                                              has_attrib_name, 0);

		    if ( ((has_attrib_value == NULL) && (attrib_value == NULL)) ||
			 ((has_attrib_value != NULL) && (attrib_value != NULL) &&
			  (strcmp(attrib_value, has_attrib_value) == 0)) ) {
		      g_free (attrib_value);
		      attrib_value =
		        o_attrib_search_object_attribs_by_name (nl_current->object_ptr,
		                                                wanted_attrib, 0);
		      if (attrib_value) {
			list = scm_cons (scm_from_utf8_string (attrib_value), list);
		      }
		      g_free (attrib_value);
		    }
		    g_free (has_attrib_name);
		    g_free (has_attrib_value);
		  }
		}
	    }
	    pl_current = pl_current->next;
	}
	nl_current = nl_current->next;
    }

    scm_dynwind_end ();
    return list;
}
