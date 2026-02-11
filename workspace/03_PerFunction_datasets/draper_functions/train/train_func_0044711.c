read_sna_from_packet(g2_packet_t *source, union combo_addr *target, const char *name)
{
	size_t rem = buffer_remaining(source->data_trunk);


	if(4 != rem &&
		INET6_ADDRLEN != rem &&
		4+2 != rem &&
		INET6_ADDRLEN+2 != rem) {
		logg_packet(STDLF" %zu", name, "SNA not an IPv4 or IPv6 address", rem);
		return false;
	}

	memset(target, 0, sizeof(*target));

	if(4 == rem || 6 == rem)
	{
		target->s.fam = AF_INET;
		target->in.sin_addr.s_addr = get_unaligned((uint32_t *) buffer_start(source->data_trunk));
		source->data_trunk.pos += sizeof(uint32_t);
		if(6 == rem)
		{
			uint16_t tmp_port = get_unaligned((uint16_t *)buffer_start(source->data_trunk));
			if(!source->big_endian)
				tmp_port = (tmp_port >> 8) | (tmp_port << 8);
			target->in.sin_port = tmp_port;
			source->data_trunk.pos += sizeof(uint16_t);
		}
	}
	else
	{
		target->s.fam = AF_INET6;
		memcpy(&target->in6.sin6_addr.s6_addr, buffer_start(source->data_trunk), INET6_ADDRLEN);
		source->data_trunk.pos += INET6_ADDRLEN;
		if(INET6_ADDRLEN+2 == rem)
		{
			uint16_t tmp_port = get_unaligned((uint16_t *)buffer_start(source->data_trunk));
			if(!source->big_endian)
				tmp_port = (tmp_port >> 8) | (tmp_port << 8);
			target->in6.sin6_port = tmp_port;
			source->data_trunk.pos += sizeof(uint16_t);
		}
	}
	casalen_ii(target);

	logg_packet_old("%s:\t%p#I\n", name, target);
	return true;
}
