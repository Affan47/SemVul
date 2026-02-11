add_conn_list(struct hda_codec *codec, hda_nid_t nid, int len,
			 const hda_nid_t *list)
{
	struct hda_conn_list *p;

	p = kmalloc(sizeof(*p) + len * sizeof(hda_nid_t), GFP_KERNEL);
	if (!p)
		return -ENOMEM;
	p->len = len;
	p->nid = nid;
	memcpy(p->conns, list, len * sizeof(hda_nid_t));
	list_add(&p->list, &codec->conn_list);
	return 0;
}
