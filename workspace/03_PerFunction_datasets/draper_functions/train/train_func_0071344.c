_e_gadcon_popup_locked_set(E_Gadcon_Popup *pop, Eina_Bool locked)
{
   if (!pop->gcc)
     return;

   e_gadcon_locked_set(pop->gcc->gadcon, locked);
   pop->gadcon_was_locked = locked;
}
