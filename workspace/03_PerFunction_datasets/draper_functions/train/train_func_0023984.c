intel_seq_print_mode(struct seq_file *m, int tabs,
				 struct drm_display_mode *mode)
{
	int i;

	for (i = 0; i < tabs; i++)
		seq_putc(m, '\t');

	seq_printf(m, "id %d:\"%s\" freq %d clock %d hdisp %d hss %d hse %d htot %d vdisp %d vss %d vse %d vtot %d type 0x%x flags 0x%x\n",
		   mode->base.id, mode->name,
		   mode->vrefresh, mode->clock,
		   mode->hdisplay, mode->hsync_start,
		   mode->hsync_end, mode->htotal,
		   mode->vdisplay, mode->vsync_start,
		   mode->vsync_end, mode->vtotal,
		   mode->type, mode->flags);
}
