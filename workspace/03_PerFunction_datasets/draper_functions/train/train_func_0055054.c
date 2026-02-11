draw ()
{
  if (!visible) return;
  CColor *col_active = &menu_colwhite;
  CColor *col_deactive = &menu_colgrey;
  CColor *col_highlight = &menu_colyellow;
  glLoadName (id);
  glEnable (GL_BLEND);
  glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glBegin (GL_QUADS);
  if (!highlight)
    glColor4ub (colback [0], colback [1], colback [2], colback [3]);
  else
    glColor4ub (255, 255, 0, colback [3]);
  glVertex3f (0.1 * x, 0.1 * y, menu_z);
  glVertex3f (0.1 * (x + w), 0.1 * y, menu_z);
  glVertex3f (0.1 * (x + w), 0.1 * (y - h), menu_z);
  glVertex3f (0.1 * x, 0.1 * (y - h), menu_z);
  glEnd ();
  glDisable (GL_BLEND);
  font1->zoom = 0.1 * (h - 0.1);
  float yf = (y - h - 0.01) / (h - 0.1);
  float xf = (x + 0.25) / (h - 0.1);
  if (active && !highlight) font1->drawText (xf, yf, menu_z, text, col_active);
  else if (!active) font1->drawText (xf, yf, menu_z, text, col_deactive);
  else font1->drawText (xf, yf, menu_z, text, col_highlight);
  font1->zoom = 0.1;
}
