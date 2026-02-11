dcb_outp_foreach(struct nvkm_bios *bios, void *data,
		 int (*exec)(struct nvkm_bios *, void *, int, u16))
{
	int ret, idx = -1;
	u8  ver, len;
	u16 outp;

	while ((outp = dcb_outp(bios, ++idx, &ver, &len))) {
		if (nvbios_rd32(bios, outp) == 0x00000000)
			break;
		if (nvbios_rd32(bios, outp) == 0xffffffff)
			break;

		if (nvbios_rd08(bios, outp) == DCB_OUTPUT_UNUSED)
			continue;
		if (nvbios_rd08(bios, outp) == DCB_OUTPUT_EOL)
			break;

		ret = exec(bios, data, idx, outp);
		if (ret)
			return ret;
	}

	return 0;
}
