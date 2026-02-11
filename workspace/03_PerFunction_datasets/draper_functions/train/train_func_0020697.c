fill_playback_urb_dsd_dop(struct snd_usb_substream *subs,
					     struct urb *urb, unsigned int bytes)
{
	struct snd_pcm_runtime *runtime = subs->pcm_substream->runtime;
	unsigned int stride = runtime->frame_bits >> 3;
	unsigned int dst_idx = 0;
	unsigned int src_idx = subs->hwptr_done;
	unsigned int wrap = runtime->buffer_size * stride;
	u8 *dst = urb->transfer_buffer;
	u8 *src = runtime->dma_area;
	u8 marker[] = { 0x05, 0xfa };


	while (bytes--) {
		if (++subs->dsd_dop.byte_idx == 3) {

			dst[dst_idx++] = marker[subs->dsd_dop.marker];
			src_idx += 2;
			subs->dsd_dop.byte_idx = 0;

			if (++subs->dsd_dop.channel % runtime->channels == 0) {

				subs->dsd_dop.marker++;
				subs->dsd_dop.marker %= ARRAY_SIZE(marker);
				subs->dsd_dop.channel = 0;
			}
		} else {

			int idx = (src_idx + subs->dsd_dop.byte_idx - 1) % wrap;

			if (subs->cur_audiofmt->dsd_bitrev)
				dst[dst_idx++] = bitrev8(src[idx]);
			else
				dst[dst_idx++] = src[idx];

			subs->hwptr_done++;
		}
	}
	if (subs->hwptr_done >= runtime->buffer_size * stride)
		subs->hwptr_done -= runtime->buffer_size * stride;
}
