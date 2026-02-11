access_proto_to_dataseq(sdp_record_t *rec, sdp_list_t *proto)
{
	sdp_data_t *seq = NULL;
	void *dtds[10], *values[10];
	void **seqDTDs, **seqs;
	int i, seqlen;
	sdp_list_t *p;

	seqlen = sdp_list_len(proto);
	seqDTDs = malloc(seqlen * sizeof(void *));
	if (!seqDTDs)
		return NULL;

	seqs = malloc(seqlen * sizeof(void *));
	if (!seqs) {
		free(seqDTDs);
		return NULL;
	}

	for (i = 0, p = proto; p; p = p->next, i++) {
		sdp_list_t *elt = p->data;
		sdp_data_t *s;
		uuid_t *uuid = NULL;
		unsigned int pslen = 0;
		for (; elt && pslen < ARRAY_SIZE(dtds); elt = elt->next, pslen++) {
			sdp_data_t *d = elt->data;
			dtds[pslen] = &d->dtd;
			switch (d->dtd) {
			case SDP_UUID16:
				uuid = (uuid_t *) d;
				values[pslen] = &uuid->value.uuid16;
				break;
			case SDP_UUID32:
				uuid = (uuid_t *) d;
				values[pslen] = &uuid->value.uuid32;
				break;
			case SDP_UUID128:
				uuid = (uuid_t *) d;
				values[pslen] = &uuid->value.uuid128;
				break;
			case SDP_UINT8:
				values[pslen] = &d->val.uint8;
				break;
			case SDP_UINT16:
				values[pslen] = &d->val.uint16;
				break;
			case SDP_SEQ8:
			case SDP_SEQ16:
			case SDP_SEQ32:
				values[pslen] = d;
				break;

			}
		}
		s = sdp_seq_alloc(dtds, values, pslen);
		if (s) {
			seqDTDs[i] = &s->dtd;
			seqs[i] = s;
			if (uuid)
				sdp_pattern_add_uuid(rec, uuid);
		}
	}
	seq = sdp_seq_alloc(seqDTDs, seqs, seqlen);
	free(seqDTDs);
	free(seqs);
	return seq;
}
