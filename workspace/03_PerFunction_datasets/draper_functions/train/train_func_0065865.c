trayxy2cl (int x, int y, int *c, int *l, GtkWidget *widget) {
	int x1, y1;
	x1 = x - (widget->allocation.width/2-tray_sz*TRAY_COLS/2);
	y1 = y - (widget->allocation.height - tray_h/2-tray_sz*TRAY_ROWS/2);
	if ((x1 >= 0) &&
	    (x1 <= tray_sz*TRAY_COLS) &&
	    (y1 >= 0) &&
	    (y1 <= tray_sz*TRAY_ROWS) &&
	    ((x1%tray_sz) != 0) &&
	    ((y1%tray_sz) != 0)) {
		*c= (int) x1 / tray_sz;
		*l= (int) y1 / tray_sz;
	} else *c = *l = -1;
}
