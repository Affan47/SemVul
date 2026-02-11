_e_kbd_int_layouts_type_get(E_Kbd_Int *ki, int type)
{
   E_Kbd_Int_Layout *kil;
   Eina_List *l;

   EINA_LIST_FOREACH(ki->layouts, l, kil)
     if (kil->type == type) return kil;
   return NULL;
}
