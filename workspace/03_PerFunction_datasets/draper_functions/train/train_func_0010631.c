vector_line(int x1, float y1, int x2, float y2) {
	if (x2<0 || x1<0) {
		gprint("Less than zero \n");
	}
	g_move(unmaph(x1),y1);
	g_line(unmaph(x2),y2);
}
