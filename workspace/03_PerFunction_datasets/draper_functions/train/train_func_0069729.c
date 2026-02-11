add_node_to_hashtables(struct node_tables * t
,		const char * nodename, cl_uuid_t id)
{
	struct rt_node_info*	idinfo = NULL;

	if (cl_uuid_is_null(&id)) {

		struct rt_node_info*	ninfo;
		if (g_hash_table_lookup(t->namemap, nodename) == NULL) {
			if (NULL == (ninfo = rt_node_info_new(nodename, id))){
				goto outofmem;
			}
			g_hash_table_insert(t->namemap,ninfo->nodename,ninfo);
			t->namecount++;
		}
		return TRUE;
	}


	if (g_hash_table_lookup(t->uuidmap,&id) == NULL) {


		if (g_hash_table_lookup(t->namemap, nodename) != NULL) {
			del_node_from_hashtables(t, nodename, nulluuid);
		}

		idinfo = rt_node_info_new(nodename, id);
		if (idinfo == NULL) {
			goto outofmem;
		}
		g_hash_table_insert(t->uuidmap, &idinfo->nodeid, idinfo);
		t->uuidcount++;
	}
	return TRUE;
outofmem:
	cl_log(LOG_ERR, "%s: out of memory", __FUNCTION__);
	return FALSE;
}
