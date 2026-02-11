_match_list_free(Eina_List *list)
{
   Match *m;

   EINA_LIST_FREE(list, m)
     {
        if (m->title) eina_stringshare_del(m->title);
        if (m->name) eina_stringshare_del(m->name);
        if (m->clas) eina_stringshare_del(m->clas);
        if (m->role) eina_stringshare_del(m->role);
        if (m->shadow_style) eina_stringshare_del(m->shadow_style);
        free(m);
     }
}
