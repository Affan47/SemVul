sdp_set_access_protos(sdp_record_t *rec, const sdp_list_t *ap)
{
	const sdp_list_t *p;
	sdp_data_t *protos = NULL;

	for (p = ap; p; p = p->next) {
		sdp_data_t *seq = access_proto_to_dataseq(rec, p->data);
		protos = sdp_seq_append(protos, seq);
	}

	sdp_attr_add(rec, SDP_ATTR_PROTO_DESC_LIST, protos);

	return 0;
}
