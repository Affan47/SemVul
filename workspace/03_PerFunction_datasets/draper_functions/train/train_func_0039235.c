Channel_ReceiveSkipSL(GF_ClientService *serv, GF_Channel *ch, const char *StreamBuf, u32 StreamLength)
{
	GF_DBUnit *au;
	if (!StreamLength) return;

	gf_es_lock(ch, 1);
	au = gf_db_unit_new();
	au->flags = GF_DB_AU_RAP;
	au->DTS = gf_clock_time(ch->clock);
	au->data = (char*)gf_malloc(sizeof(char) * (ch->media_padding_bytes + StreamLength));
	memcpy(au->data, StreamBuf, sizeof(char) * StreamLength);
	if (ch->media_padding_bytes) memset(au->data + StreamLength, 0, sizeof(char)*ch->media_padding_bytes);
	au->dataLength = StreamLength;
	au->next = NULL;


	if (ch->clock && !ch->IsClockInit) {
		if (gf_es_owns_clock(ch)) {
			gf_clock_set_time(ch->clock, 0);
			ch->IsClockInit = 1;
			ch->seed_ts = 0;
		}
		if (ch->clock->clock_init && !ch->IsClockInit) {
			ch->IsClockInit = 1;
			ch->seed_ts = gf_clock_time(ch->clock);
		}
	}

	if (!ch->AU_buffer_first) {
		ch->AU_buffer_first = au;
		ch->AU_buffer_last = au;
		ch->AU_Count = 1;
	} else {
		ch->AU_buffer_last->next = au;
		ch->AU_buffer_last = ch->AU_buffer_last->next;
		ch->AU_Count += 1;
	}

	Channel_UpdateBufferTime(ch);

	if (ch->BufferOn) {
		ch->last_au_time = gf_term_get_time(ch->odm->term);
		Channel_UpdateBuffering(ch, 1);
	}
	gf_es_lock(ch, 0);
}
