do_circle(FILE *fp)
{
  int x, y;
  unsigned int radius, color;
  struct LineStyle linestyle;
  struct FillStyle fillstyle;


  reset_attributes();


  if(fscanf(fp,"%d %d %u\n",&x, &y, &radius) != 3)
    {
      fprintf(stderr,"Error: Invalid circle record #%d in %s()\n",
	      records_processed, __func__);
      exit(1);
    }

  x *= scale;
  y *= scale;
  radius *=  scale;
  color = GRAPHIC_COLOR;

  linestyle = LINE_DEFAULT;
  fillstyle = FILL_DEFAULT;
  get_style(fp, &color, &linestyle, &fillstyle);

  circle_object(x,y,radius,color,&linestyle,&fillstyle);
}
