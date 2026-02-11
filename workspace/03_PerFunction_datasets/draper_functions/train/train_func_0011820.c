push(int, Packet *p)
{
    if (_active)
	write_packet(p, _multipacket);
    checked_output_push(0, p);
}
