_x11_elm_cnp_init(void)
{
   int i;
   static int _init_count = 0;

   if (_init_count > 0) return EINA_TRUE;
   _init_count++;
   for (i = 0; i < CNP_N_ATOMS; i++)
     {
        _x11_atoms[i].atom = ecore_x_atom_get(_x11_atoms[i].name);
        ecore_x_selection_converter_atom_add
          (_x11_atoms[i].atom, _x11_atoms[i].converter);
     }
   ecore_event_handler_add(ECORE_X_EVENT_SELECTION_CLEAR, _x11_selection_clear, NULL);
   ecore_event_handler_add(ECORE_X_EVENT_SELECTION_NOTIFY, _x11_selection_notify, NULL);
   return EINA_TRUE;
}
