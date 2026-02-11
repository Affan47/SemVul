_init_main_cb(void *data __UNUSED__, Eio_File *handler, const char *file)
{
   if (handler == eio_ls[0])
     themes = eina_list_append(themes, strdup(file));
   else if (handler == eio_ls[1])
     sthemes = eina_list_append(sthemes, strdup(file));
}
