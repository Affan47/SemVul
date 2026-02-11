gamgi_mesa_draw_orbital (gamgi_orbital *orbital)
{
gamgi_dlist *dlist;
double rotate[16];
double *center;
double scale;
int *dots;

glPushMatrix ();

center = orbital->center;
scale = orbital->object.scale;

glTranslatef (center[0], center[1], center[2]);
glScalef (scale, scale, scale);
glTranslatef (-center[0], -center[1], -center[2]);

glPushMatrix ();

glTranslatef (orbital->origin[0], orbital->origin[1], orbital->origin[2]);

gamgi_math_quaternion_to_matrix4 (orbital->quaternion, rotate);
glMultMatrixd (rotate);


dots = orbital->dots;

if (orbital->style == GAMGI_MESA_WIRED)
  {
  glLineWidth (4.0);
  if (dots[1] > 0)
    { glColor3f (orbital->base_r, orbital->base_g, orbital->base_b);
      gamgi_mesa_render_points (dots[1],
      orbital->points + 3 * dots[0]); }
  if (dots[2] > 0)
    { glColor3f (orbital->phase_r, orbital->phase_g, orbital->phase_b);
      gamgi_mesa_render_points (dots[2],
      orbital->points + 3 * dots[0] + 3 * dots[1]); }
  glLineWidth (1.0);
  }

if (orbital->style == GAMGI_MESA_SOLID)
  {
  glDisable (GL_CULL_FACE);
  if (dots[1] > 0)
    { glColor3f (orbital->base_r, orbital->base_g, orbital->base_b);
      gamgi_mesa_render_triangles (dots[1] / 3,
      orbital->points + 3 * dots[0]); }
  if (dots[2] > 0)
    { glColor3f (orbital->phase_r, orbital->phase_g, orbital->phase_b);
      gamgi_mesa_render_triangles (dots[2] / 3,
      orbital->points + 3 * dots[0] + 3 * dots[1]); }
  glEnable (GL_CULL_FACE);
  }

if (orbital->frame == TRUE)
  { glColor3f (orbital->frame_r, orbital->frame_g, orbital->frame_b);
    gamgi_mesa_render_lines (orbital->lines, orbital->points); }
if (orbital->axes > 0.0)
  gamgi_mesa_axes_orbital (orbital, TRUE);


glPopMatrix ();

dlist = orbital->text_start;
while (dlist != NULL)
  { gamgi_mesa_draw_text (GAMGI_CAST_TEXT dlist->data);
    dlist = dlist->next; }

glPopMatrix ();
}
