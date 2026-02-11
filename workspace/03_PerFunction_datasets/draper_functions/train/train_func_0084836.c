shadow_render_line(int line, unsigned char *dest, char unsigned *buffer)
{
    uint8_t  *ptr  = (void*)dest;
    uint16_t *ptr2 = (void*)dest;
    uint32_t *ptr4 = (void*)dest;
    int x;

    switch (fb_var.bits_per_pixel) {
    case 8:
	dither_line(buffer, ptr, line, swidth);
	break;
    case 15:
    case 16:
	for (x = 0; x < swidth; x++) {
	    ptr2[x] = s_lut_red[buffer[x*3]] |
		s_lut_green[buffer[x*3+1]] |
		s_lut_blue[buffer[x*3+2]];
	}
	break;
    case 24:
	for (x = 0; x < swidth; x++) {
	    ptr[3*x+2] = buffer[3*x+0];
	    ptr[3*x+1] = buffer[3*x+1];
	    ptr[3*x+0] = buffer[3*x+2];
	}
	break;
    case 32:
	for (x = 0; x < swidth; x++) {
	    ptr4[x] = s_lut_transp[255] |
		s_lut_red[buffer[x*3]] |
		s_lut_green[buffer[x*3+1]] |
		s_lut_blue[buffer[x*3+2]];
	}
	break;
    }
}
