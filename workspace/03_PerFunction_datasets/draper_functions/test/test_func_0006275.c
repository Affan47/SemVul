iscsi_destroy_session(struct iscsi_cls_session *session)
{
	iscsi_remove_session(session);
	ISCSI_DBG_TRANS_SESSION(session, "Completing session destruction\n");
	iscsi_free_session(session);
	return 0;
}
