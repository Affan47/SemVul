oo_prop_list_has (GSList *props, gboolean *threed, char const *tag)
{
	GSList *ptr;
	gboolean res;
	for (ptr = props; ptr; ptr = ptr->next) {
		OOProp *prop = ptr->data;
		if (0 == strcmp (prop->name, tag) &&
		    ((res = g_value_get_boolean (&prop->value))))
			*threed = res;
	}
}
