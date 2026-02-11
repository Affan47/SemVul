count_rice_bits_in_partition_(
	const unsigned rice_parameter,
	const unsigned partition_samples,
	const FLAC__uint64 abs_residual_partition_sum
)
{
	return
		FLAC__ENTROPY_CODING_METHOD_PARTITIONED_RICE_PARAMETER_LEN +
		(1+rice_parameter) * partition_samples +
		(
			rice_parameter?
				(unsigned)(abs_residual_partition_sum >> (rice_parameter-1))
				: (unsigned)(abs_residual_partition_sum << 1)
		)
		- (partition_samples >> 1)


	;
}
