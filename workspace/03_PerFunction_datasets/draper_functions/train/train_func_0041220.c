segae_vdp_ctrl_w ( UINT8 chip, UINT8 data )
{
	if (!segae_vdp_cmdpart[chip]) {
		segae_vdp_cmdpart[chip] = 1;
		segae_vdp_command[chip] = data;
	} else {
		segae_vdp_cmdpart[chip] = 0;
		segae_vdp_command[chip] |= (data << 8);
		segae_vdp_processcmd (chip, segae_vdp_command[chip]);
	}
}
