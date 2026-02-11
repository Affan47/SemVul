pdp_resample_scale_nn(s16 *src_image, s16 *dst_image, s32 src_w, s32 src_h, s32 dst_w, s32 dst_h)
{
    s32 i,j;
    s32 x=0;
    s32 y=0;
    s32 frac_x=0;
    s32 frac_y=0;
    s32 scale_x = (src_w << 20 ) / dst_w;
    s32 scale_y = (src_h << 20 ) / dst_h;

    for (j=0; j<dst_h; j++){
	for (i=0; i<dst_w; i++){
	    *dst_image++ = src_image[x+y];
	    frac_x += scale_x;
	    x = frac_x >> 20;
	}
	x = 0;
	frac_x = 0;
	frac_y += scale_y;
	y = (frac_y >> 20) * src_w;
    }

}
