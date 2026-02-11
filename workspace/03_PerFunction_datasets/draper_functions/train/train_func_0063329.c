adpcm_expand(
		unsigned char* &data,
		BitsReader& in,
		unsigned int insize,
		bool stereo)
	{

		if ( ! in.gotBits(2) )
		{
			IF_VERBOSE_MALFORMED_SWF(
			log_swferror(_("corrupted ADPCM header"));
			);
			return 0;
		}
		unsigned int n_bits = in.read_uint(2) + 2;


		boost::int16_t* out_data = new boost::int16_t[insize * 5];
		data = reinterpret_cast<unsigned char *>(out_data);

		boost::uint32_t sample_count = 0;

		while ( in.gotBits(22) )
		{


			int	sample = in.read_sint(16);

			int	stepsize_index = in.read_uint(6);
			assert(STEPSIZE_CT >= (1 << 6));

			if (stereo == false)
			{

				if (n_bits == 0) {
					abort();
				} else if (n_bits == 2) {
					sample_count += doMonoBlock(&out_data, 2, in, sample, stepsize_index);
				} else if (n_bits == 3) {
					sample_count += doMonoBlock(&out_data, 3, in, sample, stepsize_index);
				} else if (n_bits == 4) {
					sample_count += doMonoBlock(&out_data, 4, in, sample, stepsize_index);
				} else if (n_bits == 5) {
					sample_count += doMonoBlock(&out_data, 5, in, sample, stepsize_index);
				}
			}
			else
			{


				int	right_sample = in.read_sint(16);

				int	right_stepsize_index = in.read_uint(6);
				assert(STEPSIZE_CT >= (1 << 6));

				if (n_bits == 0) {
					abort();
				} else if (n_bits == 2) {
					sample_count += doStereoBlock(&out_data, 2, in, sample, stepsize_index, right_sample, right_stepsize_index);
				} else if (n_bits == 3) {
					sample_count += doStereoBlock(&out_data, 3, in, sample, stepsize_index, right_sample, right_stepsize_index);
				} else if (n_bits == 4) {
					sample_count += doStereoBlock(&out_data, 4, in, sample, stepsize_index, right_sample, right_stepsize_index);
				} else if (n_bits == 5) {
					sample_count += doStereoBlock(&out_data, 5, in, sample, stepsize_index, right_sample, right_stepsize_index);
				}

			}
		}
		return sample_count;

	}
