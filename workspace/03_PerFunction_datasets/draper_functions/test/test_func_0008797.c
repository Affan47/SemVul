calculate_data_blocks(struct amdtp_stream *s,
					  unsigned int syt)
{
	unsigned int phase, data_blocks;


	if (s->flags & CIP_BLOCKING) {

		if (syt == CIP_SYT_NO_INFO)
			data_blocks = 0;
		else
			data_blocks = s->syt_interval;

	} else {
		if (!cip_sfc_is_base_44100(s->sfc)) {

			data_blocks = s->data_block_state;
		} else {
			phase = s->data_block_state;


			if (s->sfc == CIP_SFC_44100)

				data_blocks = 5 + ((phase & 1) ^
						   (phase == 0 || phase >= 40));
			else

				data_blocks = 11 * (s->sfc >> 1) + (phase == 0);
			if (++phase >= (80 >> (s->sfc >> 1)))
				phase = 0;
			s->data_block_state = phase;
		}
	}

	return data_blocks;
}
