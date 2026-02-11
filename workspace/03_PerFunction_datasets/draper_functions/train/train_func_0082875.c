ast_slinfactory_read(struct ast_slinfactory *sf, short *buf, size_t samples)
{
	struct ast_frame *frame_ptr;
	unsigned int sofar = 0, ineed, remain;
	short *frame_data, *offset = buf;

	while (sofar < samples) {
		ineed = samples - sofar;

		if (sf->holdlen) {
			if (sf->holdlen <= ineed) {
				memcpy(offset, sf->offset, sf->holdlen * sizeof(*offset));
				sofar += sf->holdlen;
				offset += sf->holdlen;
				sf->holdlen = 0;
				sf->offset = sf->hold;
			} else {
				remain = sf->holdlen - ineed;
				memcpy(offset, sf->offset, ineed * sizeof(*offset));
				sofar += ineed;
				sf->offset += ineed;
				sf->holdlen = remain;
			}
			continue;
		}

		if ((frame_ptr = AST_LIST_REMOVE_HEAD(&sf->queue, frame_list))) {
			frame_data = frame_ptr->data.ptr;

			if (frame_ptr->samples <= ineed) {
				memcpy(offset, frame_data, frame_ptr->samples * sizeof(*offset));
				sofar += frame_ptr->samples;
				offset += frame_ptr->samples;
			} else {
				remain = frame_ptr->samples - ineed;
				memcpy(offset, frame_data, ineed * sizeof(*offset));
				sofar += ineed;
				frame_data += ineed;
				if (remain > (AST_SLINFACTORY_MAX_HOLD - sf->holdlen)) {
					remain = AST_SLINFACTORY_MAX_HOLD - sf->holdlen;
				}
				memcpy(sf->hold, frame_data, remain * sizeof(*offset));
				sf->holdlen = remain;
			}
			ast_frfree(frame_ptr);
		} else {
			break;
		}
	}

	sf->size -= sofar;
	return sofar;
}
