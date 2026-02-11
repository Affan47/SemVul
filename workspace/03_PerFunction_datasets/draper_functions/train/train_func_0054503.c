draw_coord(FILE *fp, double x1, double y1, int index, double delay){
double factor , upleft_x, upleft_y;
	if (frame.ur.x != 0)
		factor = (double)9500 / frame.ur.x;

	if (factor > 9500 / frame.ur.y)
		factor = (double)9500 / frame.ur.y;
	upleft_x = x1*factor + OFFSET;
	upleft_y = y1*factor + OFFSET;


	fprintf(fp,"4 0 0 50 -1 0 12 0.0000 4 150 315 %.0f %.0f %d\\001\n",upleft_x,upleft_y,index);
}
