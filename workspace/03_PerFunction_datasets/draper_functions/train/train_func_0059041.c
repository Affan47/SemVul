gtk_meta_fillh (void *p, double c[], double hue, int color, int connect)


{
	GtkMeta *meta = (GtkMeta*)p;
	GtkWidget *widget = GTK_WIDGET(meta);

	int i,ci[8];
	GdkPoint points[5];
	for (i=0; i<8; i+=2) ci[i]=(int)col(c[i]);
	for (i=1; i<8; i+=2) ci[i]=(int)row(c[i]);
	for (i=0; i<4; i++) {
		points[i].x=ci[2*i];
		points[i].y=ci[2*i+1];
	}
	points[4].x=points[0].x;
	points[4].y=points[0].y;
	sethue(meta,hue,color);
	gdk_draw_polygon(meta->draw,meta->stipplegc,1,points,4);

	if (!connect) return;
	setline(meta,0,line_solid);
	setcolor(meta,1);
	gdk_draw_lines(meta->draw,meta->gc,points,5);
}
