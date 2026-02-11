drv_Pertelian_start(const char *section)
{
    int backlight;
    int rows = -1, cols = -1;
    char *s;
    char cmd[12] = "";

    s = cfg_get(section, "Size", NULL);
    if (s == NULL || *s == '\0') {
	error("%s: no '%s.Size' entry from %s", Name, section, cfg_source());
	return -1;
    }
    if (sscanf(s, "%dx%d", &cols, &rows) != 2 || rows < 1 || cols < 1) {
	error("%s: bad %s.Size '%s' from %s", Name, section, s, cfg_source());
	free(s);
	return -1;
    }

    DROWS = rows;
    DCOLS = cols;


    if (drv_Pertelian_open(section) < 0) {
	return -1;
    }


    cmd[0] = PERTELIAN_LCDCOMMAND;
    cmd[1] = 0x38;
    cmd[2] = PERTELIAN_LCDCOMMAND;
    cmd[3] = 0x06;
    cmd[4] = PERTELIAN_LCDCOMMAND;
    cmd[5] = 0x10;
    cmd[6] = PERTELIAN_LCDCOMMAND;
    cmd[7] = 0x0c;
    cmd[8] = 0x0c;

    drv_Pertelian_send(cmd, 8);

    if (cfg_number(section, "Backlight", 0, 0, 1, &backlight) > 0) {
	drv_Pertelian_backlight(backlight);
    }

    drv_Pertelian_clear();
    return 0;
}
