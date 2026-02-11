e_int_border_menu_hooks_clear(void)
{
   E_Border_Menu_Hook *h;
   EINA_LIST_FREE(menu_hooks, h)
     free(h);
}
