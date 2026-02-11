_e_smart_del(Evas_Object *obj)
{
   INTERNAL_ENTRY;

   if (sd->del_func) sd->del_func(obj);
   while (sd->subobjs)
     {
        Evas_Object *sobj = sd->subobjs->data;


        sd->subobjs = eina_list_remove_list(sd->subobjs, sd->subobjs);
        evas_object_del(sobj);
     }
   free(sd);
}
