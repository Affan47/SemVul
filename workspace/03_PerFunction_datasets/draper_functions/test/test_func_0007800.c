_fsel_cb_close(void *data, E_Dialog *dia __UNUSED__)
{
   E_Import_Dialog *id = data;

   e_object_ref(data);
   if (id->cancel) id->cancel(id);
   e_object_del(data);
   e_object_unref(data);
}
