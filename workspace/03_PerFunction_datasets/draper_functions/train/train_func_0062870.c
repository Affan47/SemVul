gamgi_mesa_atom_draw_cross (gamgi_atom *atom)
{
if (atom->bond_start == NULL) glCallList (GAMGI_MESA_CROSS);
else
  {
  glPointSize (gamgi->atom->width);
  glBegin (GL_POINTS);
  glVertex3d (0.0, 0.0, 0.0);
  glEnd ();
  glPointSize (1.0);
  }
}
