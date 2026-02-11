buffer_despeck(PKV_DEV s, int side)
{
  SANE_Status ret = SANE_STATUS_GOOD;
  int side_index = (side == SIDE_FRONT)?0:1;

  DBG (10, "buffer_despeck: start\n");

  ret = sanei_magic_despeck(
    &s->params[side_index],s->img_buffers[side_index],s->val[OPT_SWDESPECK].w
  );
  if(ret){
    DBG (5, "buffer_despeck: bad despeck, bailing\n");
    ret = SANE_STATUS_GOOD;
    goto cleanup;
  }

  cleanup:
  DBG (10, "buffer_despeck: finish\n");
  return ret;
}
