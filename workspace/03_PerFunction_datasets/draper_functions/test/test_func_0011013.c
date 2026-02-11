restore_vga_mode(struct vgastate *state)
{
	struct regstate *saved = (struct regstate *) state->vidstate;
	unsigned short iobase;
	int i;

	vga_w(state->vgabase, VGA_MIS_W, saved->misc);

	if (saved->misc & 1)
		iobase = 0x3d0;
	else
		iobase = 0x3b0;


	vga_wseq(state->vgabase, VGA_SEQ_CLOCK_MODE,
		 saved->seq[VGA_SEQ_CLOCK_MODE] | 0x20);


	vga_wseq(state->vgabase, VGA_SEQ_RESET, 0x01);


	vga_r(state->vgabase, iobase + 0xa);
	vga_w(state->vgabase, VGA_ATT_W, 0x00);

	for (i = 2; i < state->num_seq; i++)
		vga_wseq(state->vgabase, i, saved->seq[i]);


	vga_wcrtcs(state->vgabase, iobase, 17, saved->crtc[17] & ~0x80);
	for (i = 0; i < state->num_crtc; i++)
		vga_wcrtcs(state->vgabase, iobase, i, saved->crtc[i]);

	for (i = 0; i < state->num_gfx; i++)
		vga_wgfx(state->vgabase, i, saved->gfx[i]);

	for (i = 0; i < state->num_attr; i++) {
		vga_r(state->vgabase, iobase + 0xa);
		vga_wattr(state->vgabase, i, saved->attr[i]);
	}


	vga_wseq(state->vgabase, VGA_SEQ_RESET, 0x03);

	vga_wseq(state->vgabase, VGA_SEQ_CLOCK_MODE,
		 saved->seq[VGA_SEQ_CLOCK_MODE] & ~(1 << 5));


	vga_r(state->vgabase, iobase + 0xa);
	vga_w(state->vgabase, VGA_ATT_W, 0x20);
}
