bit_putcs_unaligned(struct vc_data *vc,
				       struct fb_info *info, const u16 *s,
				       u32 attr, u32 cnt, u32 d_pitch,
				       u32 s_pitch, u32 cellsize,
				       struct fb_image *image, u8 *buf,
				       u8 *dst)
{
	u16 charmask = vc->vc_hi_font_mask ? 0x1ff : 0xff;
	u32 shift_low = 0, mod = vc->vc_font.width % 8;
	u32 shift_high = 8;
	u32 idx = vc->vc_font.width >> 3;
	u8 *src;

	while (cnt--) {
		src = vc->vc_font.data + (scr_readw(s++)&
					  charmask)*cellsize;

		if (attr) {
			update_attr(buf, src, attr, vc);
			src = buf;
		}

		fb_pad_unaligned_buffer(dst, d_pitch, src, idx,
					image->height, shift_high,
					shift_low, mod);
		shift_low += mod;
		dst += (shift_low >= 8) ? s_pitch : s_pitch - 1;
		shift_low &= 7;
		shift_high = 8 - shift_low;
	}

	info->fbops->fb_imageblit(info, image);

}
