isert_conn_create_fastreg_pool(struct isert_conn *isert_conn)
{
	struct fast_reg_descriptor *fr_desc;
	struct isert_device *device = isert_conn->device;
	struct se_session *se_sess = isert_conn->conn->sess->se_sess;
	struct se_node_acl *se_nacl = se_sess->se_node_acl;
	int i, ret, tag_num;


	tag_num = max_t(u32, ISCSIT_MIN_TAGS, se_nacl->queue_depth);
	tag_num = (tag_num * 2) + ISCSIT_EXTRA_TAGS;

	isert_conn->fr_pool_size = 0;
	for (i = 0; i < tag_num; i++) {
		fr_desc = kzalloc(sizeof(*fr_desc), GFP_KERNEL);
		if (!fr_desc) {
			isert_err("Failed to allocate fast_reg descriptor\n");
			ret = -ENOMEM;
			goto err;
		}

		ret = isert_create_fr_desc(device->ib_device,
					   device->pd, fr_desc);
		if (ret) {
			isert_err("Failed to create fastreg descriptor err=%d\n",
			       ret);
			kfree(fr_desc);
			goto err;
		}

		list_add_tail(&fr_desc->list, &isert_conn->fr_pool);
		isert_conn->fr_pool_size++;
	}

	isert_dbg("Creating conn %p fastreg pool size=%d",
		 isert_conn, isert_conn->fr_pool_size);

	return 0;

err:
	isert_conn_free_fastreg_pool(isert_conn);
	return ret;
}
