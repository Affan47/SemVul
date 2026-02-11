coolscan_get_window_param_LS30 (Coolscan_t * s, int wid,int prescanok)
{
  int translen;
  unsigned char *buf;

  DBG (10, "GET_WINDOW_PARAM\n");


  translen = window_parameter_data_block.size + window_descriptor_block_LS30.size;


  memset (s->buffer, '\0', max_WDB_size);

  set_SW_xferlen (get_window.cmd, translen);
  get_window.cmd[5]= wid;

  hexdump (15, "Get window cmd", get_window.cmd, get_window.size);
  do_scsi_cmd (s->sfd, get_window.cmd, get_window.size,
		     s->buffer, translen);

  buf = s->buffer + window_parameter_data_block.size;
  hexdump (10, "Window get", buf, 117);

  s->brightness = buf[0x32];
  s->contrast = buf[0x33];
  DBG (10, "\tbrightness=%d, contrast=%d\n", s->brightness, s->contrast);


  s->bits_per_color = get_WD_bitsperpixel (buf);

  DBG (10, "\tcolormode=%d, bits per pixel=%d\n",
       s->colormode, s->bits_per_color);

  if(prescanok)
  { switch(wid)
    { case 1: s->pretv_r = get_gain_LS30(buf);
              break;
      case 2: s->pretv_g = get_gain_LS30(buf);
              break;
      case 3: s->pretv_b = get_gain_LS30(buf);
            break;
    }
  }


  s->transfermode = get_WD_transfermode (buf);

  s->gammaselection = get_WD_gammaselection (buf);
  DBG (10, "\tpre_r=%d, pre_g=%d, preb=%d\n",
       s->pretv_r, s->pretv_g, s->pretv_b);

  DBG (5, "\tnegative=%d, dropoutcolor=%d, preview=%d, transfermode=%d, gammasel=%d\n",
       s->negative, s->dropoutcolor, s->preview, s->transfermode,
       s->gammaselection);

  DBG (10, "get_window_param - return\n");
  return 0;
}
