ndmp_sxa_fh_add_node (struct ndm_session *sess,
  struct ndmp_xa_buf *xa, struct ndmconn *ref_conn)
{
	struct ndm_control_agent *ca = &sess->control_acb;
	struct ndmlog *		ixlog = &ca->job.index_log;
	int			tagc = ref_conn->chan.name[1];
	unsigned int		i;
	ndmp9_node *		node;

	xa->reply.flags |= NDMNMB_FLAG_NO_SEND;

	NDMS_WITH_NO_REPLY(ndmp9_fh_add_node)
		for (i = 0; i < request->nodes.nodes_len; i++) {
			node = &request->nodes.nodes_val[i];

			ndmfhdb_add_node (ixlog, tagc,
				node->fstat.node.value, &node->fstat);
		}
	NDMS_ENDWITH

	return 0;
}
