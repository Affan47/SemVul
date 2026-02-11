ft_nlq_read_next(FT_INFO *handler, char *record)
{
  MI_INFO *info= (MI_INFO *) handler->info;

  if (++handler->curdoc >= handler->ndocs)
  {
    --handler->curdoc;
    return HA_ERR_END_OF_FILE;
  }

  info->update&= (HA_STATE_CHANGED | HA_STATE_ROW_CHANGED);

  info->lastpos=handler->doc[handler->curdoc].dpos;
  if (!(*info->read_record)(info,info->lastpos,(uchar*) record))
  {
    info->update|= HA_STATE_AKTIV;
    return 0;
  }
  return my_errno;
}
