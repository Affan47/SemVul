get_page_viewport(double *vx, double *vy)
{
    *vx = device_table[curdevice].pg.width/device_table[curdevice].pg.dpi;
    *vy = device_table[curdevice].pg.height/device_table[curdevice].pg.dpi;
    if (*vx < *vy) {
        *vy /= *vx;
        *vx = 1.0;
    } else {
        *vx /= *vy;
        *vy = 1.0;
    }
}
