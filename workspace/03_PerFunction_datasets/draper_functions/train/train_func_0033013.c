chip_gen_vga_write(void *_cpssp, unsigned long pa, const void *from, int len)
{
	struct cpssp *cpssp = (struct cpssp *) _cpssp;

	if (cpssp->state_power) {
		switch (cpssp->mode) {
		case VGA:
			if (vga_write(cpssp, pa, from, len) == 0) {
				return 0;
			}
			break;
		case VESA_FAUM:
			if (vesa_write(cpssp, pa, from, len) == 0) {
				return 0;
			}
			break;
		case VBE_BOCHS:
			assert(0);
			break;
		default:
			assert(0);
		}

		if (PA_VGABIOS <= pa
				&& pa <= PA_VGABIOS + cpssp->sz_vga_bios - 1) {


			return 1;

		} else {

			return 1;
		}
	} else {
		return 1;
	}
}
