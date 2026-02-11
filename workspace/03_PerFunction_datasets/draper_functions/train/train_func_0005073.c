e_gadcon_custom_new(E_Gadcon *gc)
{
   E_OBJECT_CHECK(gc);
   E_OBJECT_TYPE_CHECK(gc, E_GADCON_TYPE);

   gadcons = eina_list_append(gadcons, gc);

   if (!custom_populate_job)
     {
        custom_populate_job =
          ecore_job_add(_e_gadcon_custom_populate_job, NULL);
     }
   if (!eina_list_data_find(custom_populate_requests, gc))
     custom_populate_requests = eina_list_append(custom_populate_requests, gc);
   gc->custom = EINA_TRUE;
}
