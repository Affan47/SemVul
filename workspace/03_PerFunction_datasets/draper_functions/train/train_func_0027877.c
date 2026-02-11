write_packet(Packet *p)
{
    struct fake_pcap_pkthdr ph;

    const Timestamp& ts = p->timestamp_anno();
    if (!ts) {
	Timestamp now = Timestamp::now();
	ph.ts.tv_sec = now.sec();
	ph.ts.tv_usec = now.usec();
    } else {
	ph.ts.tv_sec = ts.sec();
	ph.ts.tv_usec = ts.usec();
    }

    unsigned to_write = p->length();
    ph.len = to_write + (_extra_length ? EXTRA_LENGTH_ANNO(p) : 0);
    if (_snaplen && to_write > _snaplen)
	to_write = _snaplen;
    ph.caplen = to_write;


    if (fwrite(&ph, sizeof(ph), 1, _fp) == 0
	|| fwrite(p->data(), 1, to_write, _fp) == 0) {
	if (errno != EAGAIN) {
	    _active = false;
	    click_chatter("ToDump(%s): %s", _filename.c_str(), strerror(errno));
	}
    } else
	_count++;
}
