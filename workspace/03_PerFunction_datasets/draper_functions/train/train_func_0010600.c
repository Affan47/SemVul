add_residual_partitioned_rice_(FLAC__BitWriter *bw, const FLAC__int32 residual[], const unsigned residual_samples, const unsigned predictor_order, const unsigned rice_parameters[], const unsigned raw_bits[], const unsigned partition_order, const FLAC__bool is_extended)
{
	const unsigned plen = is_extended? FLAC__ENTROPY_CODING_METHOD_PARTITIONED_RICE2_PARAMETER_LEN : FLAC__ENTROPY_CODING_METHOD_PARTITIONED_RICE_PARAMETER_LEN;
	const unsigned pesc = is_extended? FLAC__ENTROPY_CODING_METHOD_PARTITIONED_RICE2_ESCAPE_PARAMETER : FLAC__ENTROPY_CODING_METHOD_PARTITIONED_RICE_ESCAPE_PARAMETER;

	if(partition_order == 0) {
		unsigned i;

		if(raw_bits[0] == 0) {
			if(!FLAC__bitwriter_write_raw_uint32(bw, rice_parameters[0], plen))
				return false;
			if(!FLAC__bitwriter_write_rice_signed_block(bw, residual, residual_samples, rice_parameters[0]))
				return false;
		}
		else {
			FLAC__ASSERT(rice_parameters[0] == 0);
			if(!FLAC__bitwriter_write_raw_uint32(bw, pesc, plen))
				return false;
			if(!FLAC__bitwriter_write_raw_uint32(bw, raw_bits[0], FLAC__ENTROPY_CODING_METHOD_PARTITIONED_RICE_RAW_LEN))
				return false;
			for(i = 0; i < residual_samples; i++) {
				if(!FLAC__bitwriter_write_raw_int32(bw, residual[i], raw_bits[0]))
					return false;
			}
		}
		return true;
	}
	else {
		unsigned i, j, k = 0, k_last = 0;
		unsigned partition_samples;
		const unsigned default_partition_samples = (residual_samples+predictor_order) >> partition_order;
		for(i = 0; i < (1u<<partition_order); i++) {
			partition_samples = default_partition_samples;
			if(i == 0)
				partition_samples -= predictor_order;
			k += partition_samples;
			if(raw_bits[i] == 0) {
				if(!FLAC__bitwriter_write_raw_uint32(bw, rice_parameters[i], plen))
					return false;
				if(!FLAC__bitwriter_write_rice_signed_block(bw, residual+k_last, k-k_last, rice_parameters[i]))
					return false;
			}
			else {
				if(!FLAC__bitwriter_write_raw_uint32(bw, pesc, plen))
					return false;
				if(!FLAC__bitwriter_write_raw_uint32(bw, raw_bits[i], FLAC__ENTROPY_CODING_METHOD_PARTITIONED_RICE_RAW_LEN))
					return false;
				for(j = k_last; j < k; j++) {
					if(!FLAC__bitwriter_write_raw_int32(bw, residual[j], raw_bits[i]))
						return false;
				}
			}
			k_last = k;
		}
		return true;
	}
}
