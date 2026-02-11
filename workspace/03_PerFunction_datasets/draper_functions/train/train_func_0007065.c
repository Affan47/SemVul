_border_geometry_set(E_Border *bd, int x, int y, int w, int h, int layer)
{
   if ((bd->w != w) || (bd->h != h))
     _policy_border_resize(bd, w, h);

   if ((bd->x != x) || (bd->y != y))
     _policy_border_move(bd, x, y);

   if ((int)bd->layer != layer) e_border_layer_set(bd, layer);
}
