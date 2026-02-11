draw_objects (GLOBAL *g)
{
  int i;

  for(i=0; i<g->nobjects; i++) {
    g->objects[i].draw(g, g->objects + i);
  }
}
