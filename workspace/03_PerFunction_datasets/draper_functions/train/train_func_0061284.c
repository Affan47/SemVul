_e_menu_cb_scroll_animator(void *data __UNUSED__)
{
   double t, dt;
   double dx, dy;
   int out;
   double spd;

   t = ecore_loop_time_get();
   spd = e_config->menus_scroll_speed;
   dt = t - _e_menu_scroll_start;
   _e_menu_scroll_start = t;
   dx = 0;
   dy = 0;
   if (_e_menu_autoscroll_x)
     {
        out = _e_menu_outside_bounds_get(_e_menu_autoscroll_x, 0);
        dx = (-_e_menu_autoscroll_x) * spd * dt;
        if (_e_menu_autoscroll_x == -1)
          {
             if (dx > out) dx = out;
          }
        else
          {
             if (dx < -out) dx = -out;
          }
     }
   if (_e_menu_autoscroll_y)
     {
        out = _e_menu_outside_bounds_get(0, _e_menu_autoscroll_y);
        dy = (-_e_menu_autoscroll_y) * spd * dt;
        if (_e_menu_autoscroll_y == -1)
          {
             if (dy > out) dy = out;
          }
        else
          {
             if (dy < -out) dy = -out;
          }
     }
   _e_menu_scroll_by(dx, dy);
   _e_menu_mouse_autoscroll_check();
   if ((_e_menu_autoscroll_x == 0) && (_e_menu_autoscroll_y == 0))
     {
        _e_menu_scroll_animator = NULL;
        return 0;
     }
   return 1;
}
