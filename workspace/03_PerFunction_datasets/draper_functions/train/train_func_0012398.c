get_server_rch(struct session *s)
{
	unsigned long    hash = 0;
	struct proxy    *px   = s->be;
	unsigned long    len;
	const char      *p;
	int              ret;
	struct acl_expr  expr;
	struct acl_test  test;


	if (px->lbprm.tot_weight == 0)
		return NULL;

	memset(&expr, 0, sizeof(expr));
	memset(&test, 0, sizeof(test));

	expr.arg.str = px->hh_name;
	expr.arg_len = px->hh_len;

	ret = acl_fetch_rdp_cookie(px, s, NULL, ACL_DIR_REQ, &expr, &test);
	if (ret == 0 || (test.flags & ACL_TEST_F_MAY_CHANGE) || test.len == 0)
		return NULL;


	if (px->lbprm.tot_used == 1)
		goto hash_done;


	len = test.len;
	p = (char *)test.ptr;
	while (len) {
		hash = *p + (hash << 6) + (hash << 16) - hash;
		len--;
		p++;
	}
 hash_done:
	if (px->lbprm.algo & BE_LB_LKUP_CHTREE)
		return chash_get_server_hash(px, hash);
	else
		return map_get_server_hash(px, hash);
}
