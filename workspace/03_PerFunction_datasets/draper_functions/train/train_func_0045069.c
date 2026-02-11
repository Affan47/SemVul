mtk_parse_info(const unsigned char* data, int dataLen)
{
  unsigned short cmd;
  unsigned int bm;

  if (dataLen >= 16
      && memcmp(&data[0], &LOG_RST[0], 6) == 0
      && memcmp(&data[12], &LOG_RST[12], 4) == 0) {

    cmd = le_read16(data + 8);
    switch (data[7]) {
    case 0x02:
      bm = le_read32(data + 8);
      dbg(1, "# Log bitmask is: %.8x\n", bm);
      if (mtk_device != MTK_LOGGER) {
        bm &= 0x7fffffffU;
      }
      if (mtk_device == HOLUX_GR245) {
        bm &= ~HOLUX245_MASK;
      }
      if (mtk_info.bitmask != bm) {
        dbg(1," ########## Bitmask Change   %.8x -> %.8x ###########\n", mtk_info.bitmask, bm);
        mtk_info.track_event |= MTK_EVT_BITMASK;
      }
      mtk_info.bitmask = bm;
      mtk_info.logLen = mtk_log_len(mtk_info.bitmask);
      break;
    case 0x03:
      dbg(1, "# Log period change %.0f sec\n", cmd/10.);
      mtk_info.track_event |= MTK_EVT_PERIOD;
      mtk_info.period = cmd;
      break;
    case 0x04:
      dbg(1, "# Log distance change %.1f m\n", cmd/10.);
      mtk_info.track_event |= MTK_EVT_DISTANCE;
      mtk_info.distance = cmd;
      break;
    case 0x05:
      dbg(1, "# Log speed change %.1f km/h\n", cmd/10.);
      mtk_info.track_event |= MTK_EVT_SPEED;
      mtk_info.speed  = cmd;
      break;
    case 0x06:
      dbg(1, "# Log policy change 0x%.4x\n", cmd);
      if (cmd == 0x01) {
        dbg(1, "# Log policy change to OVERWRITE\n");
      }
      if (cmd == 0x02) {
        dbg(1, "# Log policy change to STOP\n");
      }
      break;
    case 0x07:
      if (cmd == 0x0106) {
        dbg(5, "# GPS Logger# Turned On\n");
        mtk_info.track_event |= MTK_EVT_START;
      }
      if (cmd == 0x0104) {
        dbg(5, "# GPS Logger# Log disabled\n");
      }
      break;
    default:
      dbg(1, "## Unknown INFO 0x%.2x\n", data[7]);
      break;
    }
  } else {
    if (global_opts.debug_level > 0) {
      fprintf(stderr,"#!! Invalid INFO block !! %d bytes\n >> ", dataLen);
      for (bm=0; bm<16; bm++) {
        fprintf(stderr, "%.2x ", data[bm]);
      }
      fprintf(stderr,"\n");
    }
    return 0;
  }
  return 16;
}
