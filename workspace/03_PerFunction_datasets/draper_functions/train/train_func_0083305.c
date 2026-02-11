k8_dbam_to_chip_select(struct amd64_pvt *pvt, u8 dct,
				  unsigned cs_mode, int cs_mask_nr)
{
	u32 dclr = dct ? pvt->dclr1 : pvt->dclr0;

	if (pvt->ext_model >= K8_REV_F) {
		WARN_ON(cs_mode > 11);
		return ddr2_cs_size(cs_mode, dclr & WIDTH_128);
	}
	else if (pvt->ext_model >= K8_REV_D) {
		unsigned diff;
		WARN_ON(cs_mode > 10);


		diff = cs_mode/3 + (unsigned)(cs_mode > 5);

		return 32 << (cs_mode - diff);
	}
	else {
		WARN_ON(cs_mode > 6);
		return 32 << cs_mode;
	}
}
