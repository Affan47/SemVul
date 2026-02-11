userlist_insertname (session *sess, struct User *newuser)
{
	if (!sess->usertree)
	{
		sess->usertree = tree_new ((tree_cmp_func *)nick_cmp, sess->server);
		sess->usertree_alpha = tree_new ((tree_cmp_func *)nick_cmp_alpha, sess->server);
	}

	tree_insert (sess->usertree_alpha, newuser);
	return tree_insert (sess->usertree, newuser);
}
