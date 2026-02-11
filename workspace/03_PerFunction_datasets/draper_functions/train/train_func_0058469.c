e_wizard_page_add(void *handle,
                  int (*init_cb)(E_Wizard_Page *pg, Eina_Bool *need_xdg_desktops, Eina_Bool *need_xdg_icons),
                  int (*shutdown_cb)(E_Wizard_Page *pg),
                  int (*show_cb)(E_Wizard_Page *pg),
                  int (*hide_cb)(E_Wizard_Page *pg),
                  int (*apply_cb)(E_Wizard_Page *pg)
                  )
{
   E_Wizard_Page *pg;

   pg = E_NEW(E_Wizard_Page, 1);
   if (!pg) return NULL;

   pg->handle = handle;
   pg->evas = pop->evas;

   pg->init = init_cb;
   pg->shutdown = shutdown_cb;
   pg->show = show_cb;
   pg->hide = hide_cb;
   pg->apply = apply_cb;

   pages = (E_Wizard_Page*)eina_inlist_append(EINA_INLIST_GET(pages), EINA_INLIST_GET(pg));

   return pg;
}
