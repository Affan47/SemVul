turtle_load_ontology (const gchar *turtle_subject,
                      const gchar *turtle_predicate,
                      const gchar *turtle_object)
{


	if (!g_strcmp0 (turtle_predicate, RDFS_TYPE)) {

		if (!g_strcmp0 (turtle_object, TRACKER_NS)) {

                        if (g_list_find_custom (namespaces,
                                                turtle_subject,
                                                (GCompareFunc) g_strcmp0)) {
                                g_error ("Redefining Tracker:Namespace '%s'",
                                         turtle_subject);
                        } else {
                                namespaces = g_list_prepend (namespaces, g_strdup (turtle_subject));
                        }
			return;
		}

		if (!g_strcmp0 (turtle_object, TRACKER_ONTO)) {

                        if (g_list_find_custom (ontologies,
                                                turtle_subject,
                                                (GCompareFunc) g_strcmp0)) {
                                g_error ("Redefining Tracker:Ontology '%s'",
                                         turtle_subject);
                        } else {
                                ontologies = g_list_prepend (ontologies, g_strdup (turtle_subject));
                        }
			return;
		}

		if (!g_strcmp0 (turtle_object, NRL_IFP)) {

			return;
		}


		if (exists_or_already_reported (turtle_subject)
		    && g_strcmp0 (turtle_subject, RDFS_CLASS)
		    && g_strcmp0 (turtle_subject, RDF_PROPERTY)
                    && g_strcmp0 (turtle_subject, TRACKER_ONTO)) {
			g_error ("%s is already defined", turtle_subject);
			return;
		}


		if (!exists_or_already_reported (turtle_object)) {
			g_error ("%s is a %s but %s is not defined",
			         turtle_subject, turtle_object, turtle_object);
		} else {


			if (!g_strcmp0 (turtle_object, RDF_PROPERTY)) {
				GList *link;
				link = g_list_find_custom (unknown_predicates,
				                           turtle_subject,
				                           (GCompareFunc)g_strcmp0);
				if (link) {
					unknown_predicates = g_list_remove_link (unknown_predicates,
					                                         link);
				}
			}
			known_items = g_list_prepend (known_items, g_strdup (turtle_subject));
		}
		return;
	}


	if (!g_strcmp0 (turtle_predicate, RDFS_SUBCLASSOF)
	    || !g_strcmp0 (turtle_predicate, RDFS_SUBPROPERTYOF)
	    || !g_strcmp0 (turtle_predicate, RDFS_RANGE)
	    || !g_strcmp0 (turtle_predicate, RDFS_DOMAIN)) {

		if (!exists_or_already_reported (turtle_object)) {
			g_error ("Class %s refers to %s but it is not defined",
			         turtle_subject, turtle_object);
		}
		return;
	}


	if (!exists_or_already_reported (turtle_predicate)
	    && !g_list_find_custom (unknown_predicates,
	                            turtle_predicate,
	                            (GCompareFunc) g_strcmp0)) {
		unknown_predicates = g_list_prepend (unknown_predicates,
		                                     g_strdup (turtle_predicate));
	}
}
