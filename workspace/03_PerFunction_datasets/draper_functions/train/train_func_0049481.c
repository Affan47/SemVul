static_dlist (int scope, gamgi_window *window)
{
gamgi_dlist *dlist = NULL;

switch (scope)
  {
  case STATIC_GAMGI:
  dlist = gamgi_engine_dlist_bond_gamgi (NULL);
  break;

  case STATIC_WINDOW:
  dlist = gamgi_engine_dlist_bond_window (window, NULL);
  break;

  case STATIC_LAYER:
  dlist = gamgi_engine_dlist_bond_layer (window->layer, NULL);
  break;

  case STATIC_BEFORE:
  dlist = static_before;
  break;

  case STATIC_CURRENT:
  dlist = gamgi->bonds;
  break;
  }

return dlist;
}
