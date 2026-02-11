e_menu_category_callback_add(char *category, void (*create_cb)(E_Menu *m, void *category_data, void *data), void (*free_cb)(void *data), void *data)
{
   E_Menu_Category *cat;
   E_Menu_Category_Callback *cb = NULL;

   cat = eina_hash_find(_e_menu_categories, category);
   if (!cat)
     {
        cat = calloc(1, sizeof(E_Menu_Category));
        eina_hash_add(_e_menu_categories, category, cat);
     }
   if (cat)
     {
        cb = calloc(1, sizeof(E_Menu_Category_Callback));
        if (cb)
          {
             cb->data = data;
             cb->create = create_cb;
             cb->free = free_cb;
             cb->category = eina_stringshare_add(category);
             cat->callbacks = eina_list_append(cat->callbacks, cb);
          }
     }
   return cb;
}
