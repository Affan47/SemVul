read_packet(ErrorHandler *errh)
{
    const TSHCell *cell;
    static TSHCell static_cell;
    Timestamp tv;
    Packet *p;
    bool more = true;
    _packet = 0;

  retry:

    if (!more)
	return false;


    _packet_filepos = _ff.file_pos();


    cell = reinterpret_cast<const TSHCell *>(_ff.get_aligned(_cell_size, &static_cell, errh));
    if (!cell)
	return false;


  check_times:
    uint32_t usec = ntohl(cell->timestamp_usec);
    if (_format == C_TSH)
	tv = Timestamp::make_usec(ntohl(cell->timestamp_sec), usec & 0xFFFFFF);
    else if (_format == C_FRPLUS || _format == C_FR)
	tv = Timestamp::make_usec(ntohl(cell->timestamp_sec), usec);
    if (!_have_any_times)
	prepare_times(tv);
    if (_have_first_time) {
	if (tv < _first_time)
	    goto retry;
	else
	    _have_first_time = false;
    }
    if (_have_last_time && tv >= _last_time) {
	_have_last_time = false;
	(void) _end_h->call_write(errh);
	if (!_active)
	    more = false;

	goto check_times;
    }


    if (_sampling_prob < (1 << SAMPLING_SHIFT)
	&& (click_random() & ((1<<SAMPLING_SHIFT)-1)) >= _sampling_prob)
	goto retry;


    if (_format != C_FR)
	p = _ff.get_packet_from_data(&cell->iph, _cell_size - 8, _cell_size - 8, tv.sec(), tv.subsec(), errh);
    else
	p = 0;
    if (!p)
	return false;

    fake_pcap_force_ip(p, FAKE_DLT_RAW);
    if (p->network_header_length() != sizeof(click_ip)) {
	checked_output_push(1, p);
	goto retry;
    }

    if (_format == C_TSH)
	SET_PAINT_ANNO(p, usec >> 24);
    _packet = p;
    return more;
}
