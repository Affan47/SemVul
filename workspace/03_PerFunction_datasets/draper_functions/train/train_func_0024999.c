_elm_pan_update(Elm_Pan_Smart_Data *psd)
{
   if (!psd->gravity_x && !psd->gravity_y)
     {
        evas_object_move(psd->content, psd->x - psd->px, psd->y - psd->py);
        return;
     }

   if ((!psd->px) && (!psd->py))
     {
        psd->px = psd->delta_posx * psd->gravity_x;
        psd->py = psd->delta_posy * psd->gravity_y;
     }
   psd->delta_posx += psd->content_w - psd->prev_cw;
   psd->prev_cw = psd->content_w;
   psd->delta_posy += psd->content_h - psd->prev_ch;
   psd->prev_ch = psd->content_h;

   evas_object_move(psd->content, psd->x - psd->px, psd->y - psd->py);
   psd->px = psd->delta_posx * psd->gravity_x;
   psd->py = psd->delta_posy * psd->gravity_y;
}
