list_them (GList *them,
	   get_desc_f get_his_id,
	   get_desc_f get_his_description)
{
	GList *ptr;
	guint len = 0;
	gboolean interactive;

	for (ptr = them; ptr ; ptr = ptr->next) {
		GObject *obj = ptr->data;
		char const *id;

		g_object_get (obj, "interactive-only", &interactive, NULL);
		if (interactive)
			continue;

		id = get_his_id (obj);
		if (!id) id = "";
		len = MAX (len, strlen (id));
	}

	g_printerr ("%-*s | %s\n", len,

		    "ID",
		    "Description");
	for (ptr = them; ptr ; ptr = ptr->next) {
		GObject *obj = ptr->data;
		char const *id;

		g_object_get (obj, "interactive-only", &interactive, NULL);
		if (interactive)
			continue;

		id = get_his_id (obj);
		if (!id) id = "";
		g_printerr ("%-*s | %s\n", len,
			    id,
			    (*get_his_description) (ptr->data));
	}
}
