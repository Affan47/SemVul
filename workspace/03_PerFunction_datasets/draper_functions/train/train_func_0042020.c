___device_tcp_client_close_raw_virt
   ___P((___device_stream *self,
         int direction),
        (self,
         direction)
___device_stream *self;
int direction;)
{
  ___device_tcp_client *d = ___CAST(___device_tcp_client*,self);
  int is_not_closed = 0;

  if (d->base.base.read_stage != ___STAGE_CLOSED)
    is_not_closed |= ___DIRECTION_RD;

  if (d->base.base.write_stage != ___STAGE_CLOSED)
    is_not_closed |= ___DIRECTION_WR;

  if (is_not_closed == 0)
    return ___FIX(___NO_ERR);

  if ((is_not_closed & ~direction) == 0)
    {


      d->base.base.read_stage = ___STAGE_CLOSED;
      d->base.base.write_stage = ___STAGE_CLOSED;

#ifdef USE_WIN32

      if (d->io_event != NULL)
        CloseHandle (d->io_event);

#endif

      if (CLOSE_SOCKET(d->s) != 0)
        return ERR_CODE_FROM_SOCKET_CALL;
    }
  else if (is_not_closed & direction & ___DIRECTION_RD)
    {


      if (shutdown (d->s, SHUTDOWN_RD) != 0)
        {
          ___SCMOBJ e = ERR_CODE_FROM_SOCKET_CALL;
          if (!NOT_CONNECTED(e))
            return e;
        }

      d->base.base.read_stage = ___STAGE_CLOSED;
    }
  else if (is_not_closed & direction & ___DIRECTION_WR)
    {


      if (shutdown (d->s, SHUTDOWN_WR) != 0)
        {
          ___SCMOBJ e = ERR_CODE_FROM_SOCKET_CALL;
          if (!NOT_CONNECTED(e))
            return e;
        }

      d->base.base.write_stage = ___STAGE_CLOSED;
    }

  return ___FIX(___NO_ERR);
}
