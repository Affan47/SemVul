_shutdown(void)
{
   if (e_randr_screen_info.randr_version == ECORE_X_RANDR_1_1)
     {
        _11_screen_info_free(e_randr_screen_info.rrvd_info.randr_info_11);
        e_randr_screen_info.rrvd_info.randr_info_11 = NULL;
     }
   else if (e_randr_screen_info.randr_version >= ECORE_X_RANDR_1_2)
     {
        _12_screen_info_free(e_randr_screen_info.rrvd_info.randr_info_12);
        e_randr_screen_info.rrvd_info.randr_info_12 = NULL;
     }
   _event_listeners_remove();
}
