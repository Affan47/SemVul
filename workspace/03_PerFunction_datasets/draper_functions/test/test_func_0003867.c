send_keyboard_mouse_status(void)
{
   BX_DEBUG(("XXX: prev=(%d,%d) curr=(%d,%d)",
                        prev_x, prev_y, current_x, current_y));

  if (((prev_x!=-1) && (current_x!=-1) && (prev_y!=-1) && (current_y!=-1)) ||
     (current_z != 0)) {
    int dx, dy, dz;


    dx = current_x - prev_x - warp_dx;
    dy = -(current_y - prev_y - warp_dy);
    dz = current_z;
    warp_cursor(warp_home_x-current_x, warp_home_y-current_y);

    DEV_mouse_motion_ext (dx, dy, dz, mouse_button_state);


      prev_x = current_x;
      prev_y = current_y;

  }
  else {
    if ((current_x!=-1) && (current_y!=-1)) {
      prev_x = current_x;
      prev_y = current_y;
    }
    else {
      prev_x = current_x = -1;
      prev_y = current_y = -1;
    }
  }
}
