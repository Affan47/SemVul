_e_remember_restore_cb(void *data __UNUSED__, int type __UNUSED__, void *event __UNUSED__)
{
   handlers = eina_list_free(handlers);
   if (!remembers->list) return ECORE_CALLBACK_PASS_ON;
   remember_idler_list = eina_list_clone(remembers->list);
   remember_idler = ecore_idler_add(_e_remember_restore_idler_cb, NULL);
   return ECORE_CALLBACK_PASS_ON;
}
