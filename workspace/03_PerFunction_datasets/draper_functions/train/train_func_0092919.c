skip_child(g2_packet_t *s, const char *name)
{
	bool ret_val = false;

	do
	{
		g2_packet_t child_p;
		child_p.more_bytes_needed = false;
		child_p.packet_decode = CHECK_CONTROLL_BYTE;
		ret_val = g2_packet_decode_from_packet(s, &child_p, 0);
		if(!ret_val) {
			logg_packet(STDLF, name, "broken child");
			break;
		}
		logg_packet("%s -> */%s additinaly found\n", name, g2_ptype_names[child_p.type]);
	} while(ret_val && s->packet_decode != DECODE_FINISHED);


	return ret_val;
}
