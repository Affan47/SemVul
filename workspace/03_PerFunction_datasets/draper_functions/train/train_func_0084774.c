startElement(void *userdata, const char *name, const char **attribs)
{
	xmlnode x;
	jconn j = (jconn) userdata;

	if (j->current) {

		x = xmlnode_insert_tag(j->current, name);
		xmlnode_put_expat_attribs(x, attribs);

		j->current = x;
	} else {
		x = xmlnode_new_tag(name);
		xmlnode_put_expat_attribs(x, attribs);
		if (strcmp(name, "stream:stream") == 0) {


			j->sid = xmlnode_get_attrib(x, "id");

			xmlnode_free(x);
		} else {
			j->current = x;
		}
	}
}
