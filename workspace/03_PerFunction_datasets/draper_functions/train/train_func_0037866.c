innards(
    const Fl_Label* o, int X, int Y, int W, int H, Fl_Align align,
    int data[][3], int n)
{
  Fl_Align a1 = align;
  if (a1 & FL_ALIGN_CLIP) {
    fl_clip(X, Y, W, H); a1 = (Fl_Align)(a1&~FL_ALIGN_CLIP);}
  fl_font((Fl_Font)o->font, o->size);
  for (int i = 0; i < n; i++) {
    fl_color((Fl_Color)(i < n-1 ? data[i][2] : o->color));
    fl_draw(o->value, X+data[i][0], Y+data[i][1], W, H, a1);
  }
  if (align & FL_ALIGN_CLIP) fl_pop_clip();
}
