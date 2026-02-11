pdp_imageproc_not_process(void *x, u32 width, u32 height, s16 *image)
{
    u32 *plane = (u32 *)image;
    int count = (width * height) >> 1;
    int i;

    for (i=0; i<count; i++){
	plane[i] ^= 0xffffffff;
    }
}
