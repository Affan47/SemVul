acl_fetch_avg_queue_size(struct proxy *px, struct session *l4, void *l7, int dir,
		   struct acl_expr *expr, struct acl_test *test)
{
	int nbsrv;

	test->flags = ACL_TEST_F_VOL_TEST;
	if (expr->arg_len) {

		for (px = proxy; px; px = px->next)
			if ((px->cap & PR_CAP_BE) && !strcmp(px->id, expr->arg.str))
				break;
	}
	if (!px)
		return 0;

	if (px->srv_act)
		nbsrv = px->srv_act;
	else if (px->lbprm.fbck)
		nbsrv = 1;
	else
		nbsrv = px->srv_bck;

	if (nbsrv > 0)
		test->i = (px->totpend + nbsrv - 1) / nbsrv;
	else
		test->i = px->totpend * 2;

	return 1;
}
