_ds_shadow_find(Dropshadow *ds, E_Container_Shape *es)
{
   Eina_List *l;

   for (l = ds->shadows; l; l = l->next)
     {
        Shadow *sh;

        sh = l->data;
        if (sh->shape == es) return sh;
     }
   return NULL;
}
