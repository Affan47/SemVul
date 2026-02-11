_overlay_route_free(Overlay_Route *route)
{
   Path *p;
   Path_Node *n;

   EINA_SAFETY_ON_NULL_RETURN(route);

   evas_object_del(route->obj);

   EINA_LIST_FREE (route->paths, p)
     free(p);

   EINA_LIST_FREE (route->nodes, n)
     {
        if (n->pos.address) eina_stringshare_del(n->pos.address);
        free(n);
     }

   free(route);
}
