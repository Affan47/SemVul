_notification_popups_place(void)
{
   Popup_Data *popup;
   Eina_List *l;
   int pos = 0;

   EINA_LIST_FOREACH(notification_cfg->popups, l, popup)
     {
        pos = _notification_popup_place(popup, pos);
     }

   next_pos = pos;
}
