gamgi_mesa_rotate_text_list (double angle, double *axis)
{
gamgi_layer *layer = NULL;
gamgi_text *text;
gamgi_dlist *dlist;
double rotate[9];
double quaternion[4];

for (dlist = gamgi->texts; dlist != NULL; dlist = dlist->next)
  gamgi_global_selection_text (GAMGI_CAST_TEXT dlist->data, TRUE);

for (dlist = gamgi->texts; dlist != NULL; dlist = dlist->next)
  {
  text = GAMGI_CAST_TEXT dlist->data;
  if (text->mark == FALSE)
    {
    static_layer (GAMGI_CAST_OBJECT text,
    &layer, angle, axis, quaternion, rotate);
    gamgi_mesa_rotate_text (text, quaternion, rotate, text->center);
    }
  }

for (dlist = gamgi->texts; dlist != NULL; dlist = dlist->next)
  gamgi_global_selection_text (GAMGI_CAST_TEXT dlist->data, FALSE);
}
