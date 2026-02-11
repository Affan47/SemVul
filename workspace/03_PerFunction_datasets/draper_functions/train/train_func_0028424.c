restore_vga_cmap(struct vgastate *state)
{
	struct regstate *saved = (struct regstate *) state->vidstate;
	int i;

	vga_w(state->vgabase, VGA_PEL_MSK, 0xff);


	vga_w(state->vgabase, VGA_PEL_IW, 0x00);
	for (i = 0; i < 768; i++)
		vga_w(state->vgabase, VGA_PEL_D, saved->vga_cmap[i]);
}
