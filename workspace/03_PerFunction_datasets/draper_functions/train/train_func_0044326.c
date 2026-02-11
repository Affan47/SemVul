calc_tex_coords(float img_width, float img_height,
				   float x, float y,
				   float reg_width, float reg_height,
				   unsigned flip_y, float *buf)
{
    buf[0] = x / img_width;
    buf[1] = buf[0] + reg_width / img_width;
    buf[2] = y / img_height;
    buf[3] = buf[2] + reg_height / img_height;
    if (flip_y)
    {
        buf[2] = 1.0 - buf[2];
        buf[3] = 1.0 - buf[3];
    }
}
