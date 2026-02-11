_pack_license(struct licenses *lic, Buf buffer, uint16_t protocol_version)
{
	if (protocol_version >= SLURM_14_03_PROTOCOL_VERSION) {
		packstr(lic->name, buffer);
		pack32(lic->total, buffer);
		pack32(lic->used, buffer);
	} else {
		error("\
%s: protocol_version %hu not supported", __func__, protocol_version);
	}
}
