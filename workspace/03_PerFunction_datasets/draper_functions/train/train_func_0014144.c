summary(Packet* p, StringAccum& sa, StringAccum* bad_sa) const
{
    IPSummaryDump::PacketDesc d(this, p, &sa, bad_sa, _careful_trunc, _extra_length);

    for (int i = 0; i < _prepare_fields.size(); i++)
	_prepare_fields[i]->prepare(d, _prepare_fields[i]);

    if (_binary) {
	sa.extend(4);
	for (int i = 0; i < _fields.size(); i++) {
	    d.clear_values();
	    bool ok = _fields[i]->extract(d, _fields[i]);
	    _fields[i]->outb(d, ok, _fields[i]);
	}
	*(reinterpret_cast<uint32_t*>(sa.data())) = htonl(sa.length());
    } else {
	for (int i = 0; i < _fields.size(); i++) {
	    if (i)
		sa << ' ';
	    d.clear_values();
	    if (_fields[i]->extract(d, _fields[i]) && _fields[i]->outa)
		_fields[i]->outa(d, _fields[i]);
	    else
		sa << '-';
	}
	sa << '\n';
    }

    return true;
}
