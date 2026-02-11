_e_mod_comp_src_image_get_func(void *data             __UNUSED__,
                               E_Manager *man         __UNUSED__,
                               E_Manager_Comp_Source *src)
{

   E_Comp_Win *cw = (E_Comp_Win *)src;
   if (!cw->c) return NULL;
   return cw->obj;
}
