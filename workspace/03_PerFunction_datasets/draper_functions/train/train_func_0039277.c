juttu(Obu2d *o, float t) {
  Palette *cols2=new_pal2(glass, new_col(0, -0.2, 0.4, 0.2));
  if (t<0 || t>1) return;
  pal_alpha2(cols2, 1-t);
  obu2d_draw(o, new_layer(cols2), 0, new_m2_roto(0, 400000, 14.0, 0), &m2d_ident);
}
