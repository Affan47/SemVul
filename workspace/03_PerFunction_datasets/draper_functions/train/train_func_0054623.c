controls_play (JSContext *cx, uintN argc, jsval *vp)
{
  jsval *argv = JS_ARGV (cx, vp);
  se_log_fncall_checkinit ("play");
  se_argc_check_max (3, "play");

  char *mrl = NULL;
  int32 pos = -1, pos_time = -1;

  switch (argc)
  {
  case 0:
    break;

  case 1:
    {
      JSString *str;
      se_arg_is_string (0, "play");

      str = JS_ValueToString (cx, argv[0]);

      mrl = SE_JS_ENCODE_STRING (cx, str);
      se_log ("playing '%s' from start\n", mrl);
    }
    break;

  case 2:
    {
      se_arg_is_number (0, "play");
      se_arg_is_int (1, "play");

      jsdouble posv;
      JS_ValueToNumber (cx, argv[0], &posv);
      pos = (posv >= 0 && posv < 100) ? posv * 655.35 : -1;

      JS_ValueToInt32 (cx, argv[1], &pos_time);
      mrl = NULL;
      se_log ("playing from %d, %d\n", pos, pos_time);
    }
    break;

  case 3:
    {
      se_arg_is_string (0, "play");
      se_arg_is_number (1, "play");
      se_arg_is_int (2, "play");

      JSString *str = JS_ValueToString (cx, argv[0]);

      jsdouble posv;
      JS_ValueToNumber (cx, argv[1], &posv);
      pos = (posv >= 0 && posv < 100) ? posv * 655.35 : -1;

      JS_ValueToInt32 (cx, argv[2], &pos_time);
      mrl = SE_JS_ENCODE_STRING (cx, str);
      se_log ("playing '%s' from %d, %d\n", mrl, pos, pos_time);
    }
    break;
  }

  if (mrl)
  {
    playlist_play_from (playlist_add_mrl (mrl, -1), pos, pos_time);
    SE_JS_FREE_ENCODED_STRING (cx, mrl);
  }
  else
  {
    play_item_t *item = playlist_get_current_item ();

    if (item)
    {
      switch (playlist_showing_logo () ? XINE_STATUS_IDLE : xine_get_status (stream))
      {
      case XINE_STATUS_STOP:
      case XINE_STATUS_IDLE:
	playlist_play_from (playlist_get_list_pos (), pos,
			   pos_time < 0 ? item->start_time : pos_time);
	break;
      default:
	if (pos >= 0 || pos_time >= 0)
	{
	  gtk_video_unblank_screen ((GtkVideo *)gtv);
	  xine_play (stream, pos < 0 ? 0 : pos, pos_time < 0 ? 0 : pos_time);
	}
	break;
      }
      play_item_dispose (item);
    } else
      logprintf (_("script_engine: error: no valid play item available\n"));
  }
  set_speed (XINE_SPEED_NORMAL);

  JS_SET_RVAL (cx, vp, JSVAL_VOID);
  return JS_TRUE;
}
