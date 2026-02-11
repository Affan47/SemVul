_e_shelf_bindings_del(E_Shelf *es)
{
   char buf[1024];
   E_Zone_Edge edge;

   snprintf(buf, sizeof(buf), "shelf.%d", es->id);
   for (edge = E_ZONE_EDGE_LEFT; edge <= E_ZONE_EDGE_BOTTOM_LEFT; edge++)
     e_bindings_edge_del(E_BINDING_CONTEXT_ZONE, edge,
                         E_BINDING_MODIFIER_NONE, 1, buf, NULL, 0);
}
