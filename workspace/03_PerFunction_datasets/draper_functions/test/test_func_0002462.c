gamgi_mesa_grab_graph (gamgi_graph *graph, int class,
int level, int offset, gamgi_object **objects, int *levels)
{
gamgi_dlist *dlist;
unsigned char color_old[3], color_new[3];

if (class == GAMGI_ENGINE_GRAPH)
  {


  gamgi_mesa_select_old (color_old);
  gamgi_mesa_select_new (color_new);
  glColor3ubv (color_new);


  if (levels[++offset] > 0) return offset;


  if (graph->object.selection == NULL) return offset;


  if (level == 1) objects[offset] = GAMGI_CAST_OBJECT graph;
  }


dlist = graph->text_start;
while (dlist != NULL)
  { offset = gamgi_mesa_grab_text (GAMGI_CAST_TEXT dlist->data,
    class, level, offset, objects, levels); dlist = dlist->next; }


if (class == GAMGI_ENGINE_GRAPH) glColor3ubv (color_old);

glPopMatrix ();

return offset;
}
