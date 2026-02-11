drv_Sample_contrast(int contrast)
{
    char cmd[2];


    if (contrast < 0)
	contrast = 0;
    if (contrast > 255)
	contrast = 255;


    cmd[0] = 0x04;
    cmd[1] = contrast;
    drv_Sample_send(cmd, 2);

    return contrast;
}
