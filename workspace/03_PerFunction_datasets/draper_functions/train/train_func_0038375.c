load_IC(IC *rec)
{
   ClientState *cs = &rec->cs;
   Window win = cs->client_win;

   if (win == focus_win && !current_CS) {
     current_CS = cs;
     save_CS_temp_to_current();
   }

   if (win == focus_win) {
     if (cs->im_state == HIME_STATE_DISABLED)
       hide_in_win(cs);
     else
     if (cs->im_state != HIME_STATE_DISABLED)
       show_in_win(cs);
   }

   if (cs->input_style & InputStyleOnSpot) {
     if (cs->im_state != HIME_STATE_DISABLED)
       move_IC_in_win(cs);
   } else
   if (cs->input_style & InputStyleOverSpot) {
     if (cs->im_state != HIME_STATE_DISABLED)
       move_IC_in_win(cs);
   } else
   if (cs->input_style & InputStyleRoot) {
     move_IC_in_win(cs);
   }
}
