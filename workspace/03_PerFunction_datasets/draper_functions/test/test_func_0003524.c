xnode_new_comment(xnode_t *parent, const char *text)
{
	xnode_t *xn;

	g_assert(text != NULL);

	xn = xnode_new(XNODE_T_COMMENT);
	xn->u.c.text = h_strdup(text);

	if (parent != NULL)
		xnode_add_child(parent, xn);

	return xn;
}
