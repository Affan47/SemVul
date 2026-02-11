draw ()
{
  int i;
  glDisable (GL_TEXTURE_2D);
  glBegin (GL_QUAD_STRIP);
  glColor3ub (255, 255, 255);
  float myzoom = 0.3;
  for (i = 0; i < 10; i ++)
  {
    glVertex3f (w [i].x - myzoom * cosi [phi], w [i].y, w [i].z + myzoom * sine [phi]);
    glVertex3f (w [i].x + myzoom * cosi [phi], w [i].y, w [i].z - myzoom * sine [phi]);
  }
  glEnd ();
}
