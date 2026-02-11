hdhomerun_video_thread_execute(void *arg)
{
	struct hdhomerun_video_sock_t *vs = (struct hdhomerun_video_sock_t *)arg;
	struct hdhomerun_pkt_t pkt_inst;

	while (!vs->terminate) {
		struct hdhomerun_pkt_t *pkt = &pkt_inst;
		hdhomerun_pkt_reset(pkt);


		size_t length = VIDEO_RTP_DATA_PACKET_SIZE;
		if (!hdhomerun_sock_recv(vs->sock, pkt->end, &length, 25)) {
			continue;
		}

		pkt->end += length;

		if (length == VIDEO_RTP_DATA_PACKET_SIZE) {
			hdhomerun_video_parse_rtp(vs, pkt);
			length = (int)(pkt->end - pkt->pos);
		}

		if (length != VIDEO_DATA_PACKET_SIZE) {

			continue;
		}

		pthread_mutex_lock(&vs->lock);


		size_t head = vs->head;
		uint8_t *ptr = vs->buffer + head;
		memcpy(ptr, pkt->pos, length);


		vs->packet_count++;
		hdhomerun_video_stats_ts_pkt(vs, ptr + TS_PACKET_SIZE * 0);
		hdhomerun_video_stats_ts_pkt(vs, ptr + TS_PACKET_SIZE * 1);
		hdhomerun_video_stats_ts_pkt(vs, ptr + TS_PACKET_SIZE * 2);
		hdhomerun_video_stats_ts_pkt(vs, ptr + TS_PACKET_SIZE * 3);
		hdhomerun_video_stats_ts_pkt(vs, ptr + TS_PACKET_SIZE * 4);
		hdhomerun_video_stats_ts_pkt(vs, ptr + TS_PACKET_SIZE * 5);
		hdhomerun_video_stats_ts_pkt(vs, ptr + TS_PACKET_SIZE * 6);


		head += length;
		if (head >= vs->buffer_size) {
			head -= vs->buffer_size;
		}


		if (head == vs->tail) {
			vs->overflow_error_count++;
			pthread_mutex_unlock(&vs->lock);
			continue;
		}

		vs->head = head;

		pthread_mutex_unlock(&vs->lock);
	}

	return NULL;
}
