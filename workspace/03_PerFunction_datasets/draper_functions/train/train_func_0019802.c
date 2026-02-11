static_compile_wired (const float *points,
const int *driver, int c)
{
int i;


glBegin (GL_LINE_STRIP);

i = driver[c];
while (points[i] != GAMGI_IO_CHAR)
  {
  if (points[i] == GAMGI_IO_STROKE)
    { glEnd (); glBegin (GL_LINE_STRIP); i += 1; }
  else
    {glVertex2f (points[i] / GAMGI_MESA_STROKED_SCALE,
    points[i+1] / GAMGI_MESA_STROKED_SCALE); i += 2; }
  }

glEnd ();
glTranslatef (points[c + 2] / GAMGI_MESA_STROKED_SCALE, 0.0, 0.0);

return TRUE;
}
