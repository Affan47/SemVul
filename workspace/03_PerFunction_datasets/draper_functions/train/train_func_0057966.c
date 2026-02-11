hpav_dump_enc_payload_indicate(void *buf, int len, struct ether_header *UNUSED(hdr))
{
	int avail = len;
	struct cm_enc_payload_indicate *mm = buf;
	unsigned proto = 0;

	if (mm->pid == HLE_PROTO)
		proto = 1;

	faifa_printf(out_stream, "PEKS: %s\n", get_peks_str(mm->peks));
	faifa_printf(out_stream, "HPAV Lan status: %s\n", get_avln_status_str(mm->avln_status));
	faifa_printf(out_stream, "PID: %s\n", get_pid_str(mm->pid));
	faifa_printf(out_stream, "PRN: %02hx\n", (short unsigned int)(mm->prn));
	faifa_printf(out_stream, "PMN: %02hx\n", (short unsigned int)(mm->pmn));
	faifa_printf(out_stream, "%s: ", proto ? "UUID" : "AES IV"); dump_hex(mm->aes_iv_uuid, AES_KEY_SIZE, " "); faifa_printf(out_stream, "\n");

	avail -= sizeof(*mm);

	return (len - avail);
}
