destroy_cb_list(struct script_cb **list)
{
	struct script_cb *foo;

	while( *list ) {
		foo = *list;
		*list = (*list)->next;
		pkg_free( foo );
	}
}
