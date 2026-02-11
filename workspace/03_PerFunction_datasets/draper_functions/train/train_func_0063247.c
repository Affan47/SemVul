_ds_shared_free(Dropshadow *ds)
{
   int i;

   for (i = 0; i < 4; i++)
     {
        if (ds->shared.shadow[i])
          {
             _ds_shstore_free(ds->shared.shadow[i]);
             ds->shared.shadow[i] = NULL;
          }
     }
   ds->shared.ref = 0;
}
