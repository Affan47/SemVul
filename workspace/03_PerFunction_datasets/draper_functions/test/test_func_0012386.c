e_font_available_list_parse(Eina_List *list)
{
   Eina_Hash *font_hash;
   Eina_List *next;
   void *key;

   font_hash = NULL;


   font_hash = _e_font_available_hash_add(font_hash, "Sans:style=Regular");
   font_hash = _e_font_available_hash_add(font_hash, "Sans:style=Bold");
   font_hash = _e_font_available_hash_add(font_hash, "Sans:style=Oblique");
   font_hash = _e_font_available_hash_add(font_hash, "Sans:style=Bold Oblique");

   font_hash = _e_font_available_hash_add(font_hash, "Serif:style=Regular");
   font_hash = _e_font_available_hash_add(font_hash, "Serif:style=Bold");
   font_hash = _e_font_available_hash_add(font_hash, "Serif:style=Oblique");
   font_hash = _e_font_available_hash_add(font_hash, "Serif:style=Bold Oblique");

   font_hash = _e_font_available_hash_add(font_hash, "Monospace:style=Regular");
   font_hash = _e_font_available_hash_add(font_hash, "Monospace:style=Bold");
   font_hash = _e_font_available_hash_add(font_hash, "Monospace:style=Oblique");
   font_hash = _e_font_available_hash_add(font_hash, "Monospace:style=Bold Oblique");

   EINA_LIST_FOREACH(list, next, key)
     font_hash = _e_font_available_hash_add(font_hash, key);

   return font_hash;
}
