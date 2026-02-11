_12_screen_info_crtc_info_get(const Ecore_X_Randr_Crtc crtc)
{
   Eina_List *iter;
   E_Randr_Crtc_Info *crtc_info;

   EINA_SAFETY_ON_TRUE_RETURN_VAL(E_RANDR_12_NO_CRTCS, NULL);

   EINA_LIST_FOREACH(e_randr_screen_info.rrvd_info.randr_info_12->crtcs, iter, crtc_info)
     {
        if (crtc_info && (crtc_info->xid == crtc)) return crtc_info;
     }
   return NULL;
}
