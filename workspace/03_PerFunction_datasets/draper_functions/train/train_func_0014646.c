hime_im_client_forward_key_press(HIME_client_handle *handle,
                                          KeySym key, u_int state,
                                          char **rstr)
{
  int flag;
  if (!handle)
    return 0;

  if (!BITON(handle->flag, FLAG_HIME_client_handle_has_focus)) {
    hime_im_client_focus_in(handle);
    handle->flag |= FLAG_HIME_client_handle_has_focus;
    hime_im_client_set_cursor_location(handle, handle->spot_location.x,
       handle->spot_location.y);
  }


  flag = hime_im_client_forward_key_event(
             handle, HIME_req_key_press, key, state, rstr);

  return ((flag & HIME_reply_key_processed) !=0);
}
