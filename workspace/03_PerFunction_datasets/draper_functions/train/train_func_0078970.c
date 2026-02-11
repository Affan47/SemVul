_e_fwin_pan_scroll_update(E_Fwin_Page *page)
{
   Edje_Message_Int_Set *msg;

   if ((page->fm_pan.x == page->fm_pan_last.x) &&
       (page->fm_pan.y == page->fm_pan_last.y) &&
       (page->fm_pan.max_x == page->fm_pan_last.max_x) &&
       (page->fm_pan.max_y == page->fm_pan_last.max_y) &&
       (page->fm_pan.w == page->fm_pan_last.w) &&
       (page->fm_pan.h == page->fm_pan_last.h)) return;
   msg = alloca(sizeof(Edje_Message_Int_Set) -
                sizeof(int) + (6 * sizeof(int)));
   msg->count = 6;
   msg->val[0] = page->fm_pan.x;
   msg->val[1] = page->fm_pan.y;
   msg->val[2] = page->fm_pan.max_x;
   msg->val[3] = page->fm_pan.max_y;
   msg->val[4] = page->fm_pan.w;
   msg->val[5] = page->fm_pan.h;


   if (page->fwin->under_obj && page->fwin->wallpaper_is_edj)
     edje_object_message_send(page->fwin->under_obj, EDJE_MESSAGE_INT_SET, 1, msg);
   if (page->fwin->over_obj)
     edje_object_message_send(page->fwin->over_obj, EDJE_MESSAGE_INT_SET, 1, msg);
   if (page->scr)
     edje_object_message_send(e_scrollframe_edje_object_get(page->scr), EDJE_MESSAGE_INT_SET, 1, msg);
   page->fm_pan_last.x = page->fm_pan.x;
   page->fm_pan_last.y = page->fm_pan.y;
   page->fm_pan_last.max_x = page->fm_pan.max_x;
   page->fm_pan_last.max_y = page->fm_pan.max_y;
   page->fm_pan_last.w = page->fm_pan.w;
   page->fm_pan_last.h = page->fm_pan.h;
}
