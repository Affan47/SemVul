rv515_gpu_init(struct radeon_device *rdev)
{
	unsigned pipe_select_current, gb_pipe_select, tmp;

	if (r100_gui_wait_for_idle(rdev)) {
		printk(KERN_WARNING "Failed to wait GUI idle while "
		       "resetting GPU. Bad things might happen.\n");
	}
	rv515_vga_render_disable(rdev);
	r420_pipes_init(rdev);
	gb_pipe_select = RREG32(R400_GB_PIPE_SELECT);
	tmp = RREG32(R300_DST_PIPE_CONFIG);
	pipe_select_current = (tmp >> 2) & 3;
	tmp = (1 << pipe_select_current) |
	      (((gb_pipe_select >> 8) & 0xF) << 4);
	WREG32_PLL(0x000D, tmp);
	if (r100_gui_wait_for_idle(rdev)) {
		printk(KERN_WARNING "Failed to wait GUI idle while "
		       "resetting GPU. Bad things might happen.\n");
	}
	if (rv515_mc_wait_for_idle(rdev)) {
		printk(KERN_WARNING "Failed to wait MC idle while "
		       "programming pipes. Bad things might happen.\n");
	}
}
