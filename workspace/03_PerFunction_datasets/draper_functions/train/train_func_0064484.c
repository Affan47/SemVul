slurmdbd_pack_modify_msg(dbd_modify_msg_t *msg,
				     uint16_t rpc_version,
				     slurmdbd_msg_type_t type,
				     Buf buffer)
{
	void (*my_cond) (void *object, uint16_t rpc_version, Buf buffer);
	void (*my_rec) (void *object, uint16_t rpc_version, Buf buffer);

	switch(type) {
	case DBD_MODIFY_ACCOUNTS:
		my_cond = slurmdb_pack_account_cond;
		my_rec = slurmdb_pack_account_rec;
		break;
	case DBD_MODIFY_ASSOCS:
		my_cond = slurmdb_pack_association_cond;
		my_rec = slurmdb_pack_association_rec;
		break;
	case DBD_MODIFY_CLUSTERS:
		my_cond = slurmdb_pack_cluster_cond;
		my_rec = slurmdb_pack_cluster_rec;
		break;
	case DBD_MODIFY_JOB:
		my_cond = slurmdb_pack_job_modify_cond;
		my_rec = slurmdb_pack_job_rec;
		break;
	case DBD_MODIFY_QOS:
		my_cond = slurmdb_pack_qos_cond;
		my_rec = slurmdb_pack_qos_rec;
		break;
	case DBD_MODIFY_USERS:
		my_cond = slurmdb_pack_user_cond;
		my_rec = slurmdb_pack_user_rec;
		break;
	default:
		fatal("Unknown pack type");
		return;
	}
	(*(my_cond))(msg->cond, rpc_version, buffer);
	(*(my_rec))(msg->rec, rpc_version, buffer);
}
