add_entropy_coding_method_(FLAC__BitWriter *bw, const FLAC__EntropyCodingMethod *method)
{
	if(!FLAC__bitwriter_write_raw_uint32(bw, method->type, FLAC__ENTROPY_CODING_METHOD_TYPE_LEN))
		return false;
	switch(method->type) {
		case FLAC__ENTROPY_CODING_METHOD_PARTITIONED_RICE:
		case FLAC__ENTROPY_CODING_METHOD_PARTITIONED_RICE2:
			if(!FLAC__bitwriter_write_raw_uint32(bw, method->data.partitioned_rice.order, FLAC__ENTROPY_CODING_METHOD_PARTITIONED_RICE_ORDER_LEN))
				return false;
			break;
		default:
			FLAC__ASSERT(0);
	}
	return true;
}
