nvbios_perf_table(struct nvkm_bios *bios, u8 *ver, u8 *hdr,
		  u8 *cnt, u8 *len, u8 *snr, u8 *ssz)
{
	struct bit_entry bit_P;
	u16 perf = 0x0000;

	if (!bit_entry(bios, 'P', &bit_P)) {
		if (bit_P.version <= 2) {
			perf = nvbios_rd16(bios, bit_P.offset + 0);
			if (perf) {
				*ver = nvbios_rd08(bios, perf + 0);
				*hdr = nvbios_rd08(bios, perf + 1);
				if (*ver >= 0x40 && *ver < 0x41) {
					*cnt = nvbios_rd08(bios, perf + 5);
					*len = nvbios_rd08(bios, perf + 2);
					*snr = nvbios_rd08(bios, perf + 4);
					*ssz = nvbios_rd08(bios, perf + 3);
					return perf;
				} else
				if (*ver >= 0x20 && *ver < 0x40) {
					*cnt = nvbios_rd08(bios, perf + 2);
					*len = nvbios_rd08(bios, perf + 3);
					*snr = nvbios_rd08(bios, perf + 4);
					*ssz = nvbios_rd08(bios, perf + 5);
					return perf;
				}
			}
		}
	}

	if (bios->bmp_offset) {
		if (nvbios_rd08(bios, bios->bmp_offset + 6) >= 0x25) {
			perf = nvbios_rd16(bios, bios->bmp_offset + 0x94);
			if (perf) {
				*hdr = nvbios_rd08(bios, perf + 0);
				*ver = nvbios_rd08(bios, perf + 1);
				*cnt = nvbios_rd08(bios, perf + 2);
				*len = nvbios_rd08(bios, perf + 3);
				*snr = 0;
				*ssz = 0;
				return perf;
			}
		}
	}

	return 0x0000;
}
