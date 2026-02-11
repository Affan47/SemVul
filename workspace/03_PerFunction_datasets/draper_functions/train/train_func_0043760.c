test_if_create_new_users(THD *thd)
{
  Security_context *sctx= thd->security_ctx;
  bool create_new_users= test(sctx->master_access & INSERT_ACL) ||
                         (!opt_safe_user_create &&
                          test(sctx->master_access & CREATE_USER_ACL));
  if (!create_new_users)
  {
    TABLE_LIST tl;
    ulong db_access;
    tl.init_one_table(C_STRING_WITH_LEN("mysql"),
                      C_STRING_WITH_LEN("user"), "user", TL_WRITE);
    create_new_users= 1;

    db_access=acl_get(sctx->get_host()->ptr(), sctx->get_ip()->ptr(),
		      sctx->priv_user, tl.db, 0);
    if (!(db_access & INSERT_ACL))
    {
      if (check_grant(thd, INSERT_ACL, &tl, FALSE, UINT_MAX, TRUE))
	create_new_users=0;
    }
  }
  return create_new_users;
}
