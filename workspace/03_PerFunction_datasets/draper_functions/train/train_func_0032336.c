draw_horbarchart(int x,int y,int w,int h,
			     int numb, FL_CHART_ENTRY entries[],
			     double min, double max, int autosize, int maxnumb,
			     Fl_Color textcolor)


{
  int i;
  double lw = 0.0;

  for (i=0; i<numb; i++) {
      double w1 = fl_width(entries[i].str);
      if (w1 > lw) lw = w1;
  }
  if (lw > 0.0) lw += 4.0;
  double incr;
  int zeroh;
  if (max == min) incr = w;
  else incr = w/(max-min);
  if ( (-min*incr) < lw) {
      incr = (w - lw + min*incr)/(max-min);
      zeroh = x+(int)rint(lw);
  } else {
      zeroh = (int)rint(x-min * incr);
  }
  int bwidth = (int)rint(h/double(autosize?numb:maxnumb));

  fl_color(textcolor);
  fl_line(zeroh, y, zeroh, y+h);
  if (min == 0.0 && max == 0.0) return;

  for (i=0; i<numb; i++) {
      int ww = (int)rint(entries[i].val*incr);
      if (ww > 0)
	fl_rectbound(zeroh,y+i*bwidth,ww+1,bwidth+1, (Fl_Color)entries[i].col);
      else if (ww < 0)
	fl_rectbound(zeroh+ww,y+i*bwidth,-ww+1,bwidth+1,(Fl_Color)entries[i].col);
  }

  fl_color(textcolor);
  for (i=0; i<numb; i++)
      fl_draw(entries[i].str,
	      zeroh-2,y+i*bwidth+bwidth/2,0,0,
	      FL_ALIGN_RIGHT);
}
