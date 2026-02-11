qlt_find_sess_invalidate_other(struct qla_tgt *tgt, uint64_t wwn,
    port_id_t port_id, uint16_t loop_id, struct qla_tgt_sess **conflict_sess)
{
	struct qla_tgt_sess *sess = NULL, *other_sess;
	uint64_t other_wwn;

	*conflict_sess = NULL;

	list_for_each_entry(other_sess, &tgt->sess_list, sess_list_entry) {

		other_wwn = wwn_to_u64(other_sess->port_name);

		if (wwn == other_wwn) {
			WARN_ON(sess);
			sess = other_sess;
			continue;
		}


		if (port_id.b24 == other_sess->s_id.b24) {
			if (loop_id != other_sess->loop_id) {
				ql_dbg(ql_dbg_tgt_tmr, tgt->vha, 0x1000c,
				    "Invalidating sess %p loop_id %d wwn %llx.\n",
				    other_sess, other_sess->loop_id, other_wwn);


				qlt_schedule_sess_for_deletion(other_sess, true);
			} else {


				other_sess->keep_nport_handle = 1;
				*conflict_sess = other_sess;
				qlt_schedule_sess_for_deletion(other_sess,
				    true);
			}
			continue;
		}


		if (loop_id == other_sess->loop_id) {
			ql_dbg(ql_dbg_tgt_tmr, tgt->vha, 0x1000d,
			       "Invalidating sess %p loop_id %d wwn %llx.\n",
			       other_sess, other_sess->loop_id, other_wwn);


			qlt_schedule_sess_for_deletion(other_sess, true);
		}
	}

	return sess;
}
