check_node_name_chars(struct check *c, struct node *dt,
				  struct node *node)
{
	int n = strspn(node->name, c->data);

	if (n < strlen(node->name))
		FAIL(c, "Bad character '%c' in node %s",
		     node->name[n], node->fullpath);
}
