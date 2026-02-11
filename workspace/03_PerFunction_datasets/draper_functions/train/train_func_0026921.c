plotchar(long *place, struct LOC_plottext *text)
{
  text->heightfont = text->font[*place + 1];
  text->yfactor = text->height / text->heightfont;
  text->xfactor = text->yfactor;
  *place += 3;
  do {
    (*place)++;
    text->coord = text->font[*place - 1];
    if (text->coord > 0)
      text->penstatus = pendown;
    else
      text->penstatus = penup;
    text->coord = abs(text->coord);
    text->coord %= 10000;
    text->xfont = (text->coord / 100 - xstart) * text->xfactor;
    text->yfont = (text->coord % 100 - ystart) * text->yfactor;
    text->xplot = text->xx + (text->xfont * text->cosslope +
                              text->yfont * text->sinslope) * text->compress;
    text->yplot = text->yy - text->xfont * text->sinslope +
      text->yfont * text->cosslope;
    plot(text->penstatus, text->xplot, text->yplot);
  } while (abs(text->font[*place - 1]) < 10000);
  text->xx = text->xplot;
  text->yy = text->yplot;
}
