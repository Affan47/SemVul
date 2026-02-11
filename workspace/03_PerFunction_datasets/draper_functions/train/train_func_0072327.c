get_console_size(Gpm_Event *ePtr)
{
   int i, prevmaxx, prevmaxy;
   struct mouse_features *which_mouse;


   prevmaxx = maxx; prevmaxy = maxy;

   i=open_console(O_RDONLY);
   ioctl(i, TIOCGWINSZ, &win);
   close(i);
   if (!win.ws_col || !win.ws_row) {
      gpm_report(GPM_PR_DEBUG,GPM_MESS_ZERO_SCREEN_DIM);
      win.ws_col=80; win.ws_row=25;
   }
   maxx=win.ws_col; maxy=win.ws_row;
   gpm_report(GPM_PR_DEBUG,GPM_MESS_SCREEN_SIZE,maxx,maxy);

   if (!prevmaxx) {
      statusX = ePtr->x = maxx/2;
      statusY = ePtr->y = maxy/2;
   } else {
      statusX = ePtr->x = ePtr->x * maxx / prevmaxx;
      statusY = ePtr->y = ePtr->y * maxy / prevmaxy;
   }

   for (i=1; i <= 1+opt_double; i++) {
      which_mouse=mouse_table+i;


     (which_mouse->opt_scaley)=(which_mouse->opt_scale)*50*maxx/80/maxy;
     gpm_report(GPM_PR_DEBUG,GPM_MESS_X_Y_VAL,(which_mouse->opt_scale),(which_mouse->opt_scaley));
   }
}
