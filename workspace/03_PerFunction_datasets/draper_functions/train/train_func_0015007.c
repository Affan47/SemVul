perform_dialog(MYSQL_PLUGIN_VIO *vio, MYSQL *mysql)
{
  unsigned char *pkt, cmd= 0;
  int pkt_len, res;
  char reply_buf[1024], *reply;

  do
  {

    pkt_len= vio->read_packet(vio, &pkt);
    if (pkt_len < 0)
      return CR_ERROR;

    if (pkt == 0)
    {


      reply= mysql->passwd;
    }
    else
    {
      cmd= *pkt++;


      if (cmd == 0 || cmd == 254)
        return CR_OK_HANDSHAKE_COMPLETE;


      if ((cmd >> 1) == 2 && *pkt == 0)
        reply= mysql->passwd;
      else
        reply= ask(mysql, cmd >> 1, (const char *) pkt,
				   reply_buf, sizeof(reply_buf));
      if (!reply)
        return CR_ERROR;
    }

    res= vio->write_packet(vio, (const unsigned char *) reply,
						   strlen(reply)+1);

    if (reply != mysql->passwd && reply != reply_buf)
      free(reply);

    if (res)
      return CR_ERROR;


  } while ((cmd & 1) != 1);


  return CR_OK;
}
