camel_imapx_store_summary_namespace_find_by_path (CamelIMAPXStoreSummary *s,
                                                  const gchar *path)
{
	gint len;
	CamelIMAPXStoreNamespace *ns;


	ns = s->namespaces->personal;
	while (ns) {
		len = strlen (ns->prefix);
		if (len == 0
		    || (strncmp (ns->prefix, path, len) == 0
			&& (path[len] == '/' || path[len] == 0)))
			break;
		ns = NULL;
	}


	return ns;
}
