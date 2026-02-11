_tabs_clear(Tab_View *v)
{
   Eina_List *l;
   Tab *tab;

   e_box_freeze(v->o_tabs);
   EINA_LIST_FOREACH (v->tabs, l, tab)
     {
        if (!tab->plugin)
          continue;

        e_box_unpack(tab->o_tab);
        evas_object_hide(tab->o_tab);
     }
   e_box_thaw(v->o_tabs);
}
