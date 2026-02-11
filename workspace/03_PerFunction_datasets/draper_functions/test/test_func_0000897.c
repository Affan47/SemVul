draw_tree_rec(ModeInfo * mi, double thick, int x, int y, double angle)
{
  treestruct *tree = &trees[MI_SCREEN(mi)];
  Display    *display = MI_DISPLAY(mi);
  GC          gc = MI_GC(mi);
  int         length = (24+NRAND(12))*tree->size;
  int         a = (int) (x - length*sin(angle));
  int         b = (int) (y - length*cos(angle));
  int         i;

  draw_line(mi, x, y, a, b, angle, thick*tree->size, 0.68*thick*tree->size);

  if (thick > 2) {
    draw_tree_rec(mi, 0.68*thick, a, b, 0.8*angle+rRand(-0.2, 0.2));
    if (thick < tree->thick-1) {
      draw_tree_rec(mi, 0.68*thick, a, b, angle+rRand(0.2, 0.9));
      draw_tree_rec(mi, 0.68*thick, (a+x)/2, (b+y)/2, angle-rRand(0.2, 0.9));
    }
  }

  if (thick < 0.5*tree->thick) {
  	int     nleaf = 12 + NRAND(4);
	  XArc    leaf[16];
    for (i = 0; i < nleaf; i++) {
      leaf[i].x = a + (int) (tree->size * rRand(-12, 12));
      leaf[i].y = b + (int) (tree->size * rRand(-12, 12));
      leaf[i].width = (int) (tree->size * rRand(2, 6));
      leaf[i].height = leaf[i].width;
      leaf[i].angle1 = 0;
      leaf[i].angle2 = 360 * 64;
    }
    if (mi->npixels >= 4)
      XSetForeground(display, gc, colors[tree->color+NRAND(4)].pixel);
    XFillArcs(display, MI_WINDOW(mi), gc, leaf, nleaf);
  }
}
