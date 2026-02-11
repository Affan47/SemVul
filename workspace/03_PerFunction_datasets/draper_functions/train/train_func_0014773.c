redraw()
{
  int cw, ch;
  stack_get_card_size (&cw, &ch);
  if (xlogo->w < table_width - 8*cw && xlogo->h < ch)
      put_picture(xlogo, table_width/2-xlogo->w/2, ch/2-xlogo->h/2,
		  0, 0, xlogo->h, xlogo->w);
  stack_redraw();
  redraw_arrows();
}
