gamgi_mesa_grab_text (gamgi_text *text, int class,
int level, int offset, gamgi_object **objects, int *levels)
{
gamgi_dlist *dlist;
unsigned char color_old[3], color_new[3];
double rotate[16];

if (class == GAMGI_ENGINE_TEXT)
  {


  gamgi_mesa_select_old (color_old);
  gamgi_mesa_select_new (color_new);
  glColor3ubv (color_new);


  if (levels[++offset] > 0) return offset;


  if (text->object.selection == NULL) return offset;


  if (level == 1) objects[offset] = GAMGI_CAST_OBJECT text;
  }

glPushMatrix ();

glTranslatef (text->center[0], text->center[1], text->center[2]);
glScalef (text->object.scale, text->object.scale, text->object.scale);
glTranslatef (-text->center[0], -text->center[1], -text->center[2]);


if (class >= GAMGI_ENGINE_TEXT)
  {
  glPushMatrix ();

  glTranslatef (text->origin[0], text->origin[1], text->origin[2]);
  gamgi_math_quaternion_to_matrix4 (text->quaternion, rotate);
  glMultMatrixd (rotate);

  if (text->style == GAMGI_MESA_WIRED)
    glLineWidth (GAMGI_MESA_STROKED_WIDTH);
  gamgi_mesa_text_draw (text);
  if (text->style == GAMGI_MESA_WIRED)
    glLineWidth (1.0);

  glPopMatrix ();
  }


dlist = text->text_start;
while (dlist != NULL)
  { offset = gamgi_mesa_grab_text (GAMGI_CAST_TEXT dlist->data,
    class, level, offset, objects, levels); dlist = dlist->next; }


if (class == GAMGI_ENGINE_TEXT) glColor3ubv (color_old);

glPopMatrix ();

return offset;
}
