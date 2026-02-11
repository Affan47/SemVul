_osd_req_encode_olist(struct osd_request *or,
	struct osd_obj_id_list *list)
{
	struct osd_cdb_head *cdbh = osd_cdb_head(&or->cdb);

	if (osd_req_is_ver1(or)) {
		cdbh->v1.list_identifier = list->list_identifier;
		cdbh->v1.start_address = list->continuation_id;
	} else {
		cdbh->v2.list_identifier = list->list_identifier;
		cdbh->v2.start_address = list->continuation_id;
	}
}
