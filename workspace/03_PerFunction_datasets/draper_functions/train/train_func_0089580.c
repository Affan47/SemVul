_rename_ok(void *data, char *text)
{
   Config_Entry *ce = data;
   const char *name;
   Evas_Object *list;

   name = eina_stringshare_add(text);
   if (name == ce->id)
     {
        eina_stringshare_del(name);
        return;
     }
   if (name == ce->entry->id)
     {
        eina_stringshare_del(name);
        if (!ce->id) return;
        eina_stringshare_replace(&ce->id, NULL);
     }
   else
     eina_stringshare_replace(&ce->id, text);
   list = ce->entry->transient ? qa_mod->cfd->cfdata->o_list_transient : qa_mod->cfd->cfdata->o_list_entry;
   e_widget_ilist_clear(list);
   _list_fill(qa_mod->cfd->cfdata, list, ce->entry->transient);
}
