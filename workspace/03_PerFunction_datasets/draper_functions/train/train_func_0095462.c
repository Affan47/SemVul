_ds_shadow_obj_init(Shadow *sh)
{
   E_Container *con;
   int i;

   if (sh->initted) return;
   sh->initted = 1;
   con = e_container_shape_container_get(sh->shape);
   for (i = 0; i < 4; i++)
     {
        sh->object[i] = evas_object_image_add(con->bg_evas);
        evas_object_image_alpha_set(sh->object[i], 1);
        evas_object_layer_set(sh->object[i], 10);
        evas_object_pass_events_set(sh->object[i], 1);
        evas_object_move(sh->object[i], 0, 0);
        evas_object_resize(sh->object[i], 0, 0);
        evas_object_color_set(sh->object[i],
                              0, 0, 0,
                              255 * sh->ds->conf->shadow_darkness);
        if (sh->visible)
          evas_object_show(sh->object[i]);
     }
}
