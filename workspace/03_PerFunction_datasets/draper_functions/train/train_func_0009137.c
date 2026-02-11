write_packet(Packet* p, int multipacket)
{
    if (multipacket > 0 && EXTRA_PACKETS_ANNO(p) > 0) {
	uint32_t count = 1 + EXTRA_PACKETS_ANNO(p);
	uint32_t total_len = p->length(), len = p->length();
	if (_extra_length)
	    total_len += EXTRA_LENGTH_ANNO(p);
	if (total_len < count * len)
	    total_len = count * len;


	Timestamp end_timestamp = p->timestamp_anno();
	Timestamp timestamp_delta;
	if (FIRST_TIMESTAMP_ANNO(p)) {
	    timestamp_delta = (end_timestamp - FIRST_TIMESTAMP_ANNO(p)) / (count - 1);
	    p->set_timestamp_anno(FIRST_TIMESTAMP_ANNO(p));
	} else
	    timestamp_delta = Timestamp();

	SET_EXTRA_PACKETS_ANNO(p, 0);
	for (uint32_t i = count; i > 0; i--) {
	    uint32_t l = total_len / i;
	    SET_EXTRA_LENGTH_ANNO(p, l - len);
	    total_len -= l;
	    write_packet(p, -1);
	    if (i == 1)
		p->timestamp_anno() = end_timestamp;
	    else
		p->timestamp_anno() += timestamp_delta;
	}

    } else {
	_sa.clear();
	_bad_sa.clear();

	summary(p, _sa, (_bad_packets ? &_bad_sa : 0));

	if (_bad_packets && _bad_sa)
	    write_line(_bad_sa.take_string());
	ignore_result(fwrite(_sa.data(), 1, _sa.length(), _f));

	_output_count++;
    }
}
