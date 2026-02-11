execute_virtual_checks(bx_segment_reg_t *seg, Bit32u offset, unsigned length)
{
  Bit32u upper_limit;

  if (seg->cache.valid==0) {
    BX_DEBUG(("execute_virtual_checks(): segment descriptor not valid"));
    return 0;
  }

  if (seg->cache.p == 0) {
    BX_ERROR(("execute_virtual_checks(): segment not present"));
    return 0;
  }

  switch (seg->cache.type) {
    case 0: case 1:
    case 2: case 3:
    case 10: case 11:
    case 14: case 15:
      if (offset > (seg->cache.u.segment.limit_scaled - length + 1)
          || (length-1 > seg->cache.u.segment.limit_scaled))
      {
        BX_ERROR(("execute_virtual_checks(): read beyond limit"));
        return 0;
      }
      if (seg->cache.u.segment.limit_scaled >= 15) {


        seg->cache.valid |= SegAccessROK;
      }
      break;

    case 8: case 9:
    case 12: case 13:
      if (offset > (seg->cache.u.segment.limit_scaled - length + 1)
          || (length-1 > seg->cache.u.segment.limit_scaled))
      {
        BX_ERROR(("execute_virtual_checks(): read beyond limit execute only"));
        return 0;
      }
      break;

    case 4: case 5:
    case 6: case 7:
      if (seg->cache.u.segment.d_b)
        upper_limit = 0xffffffff;
      else
        upper_limit = 0x0000ffff;
      if ((offset <= seg->cache.u.segment.limit_scaled) ||
           (offset > upper_limit) || ((upper_limit - offset) < (length - 1)))
      {
        BX_ERROR(("execute_virtual_checks(): read beyond limit ED"));
        return 0;
      }
      break;

    default:
      BX_PANIC(("execute_virtual_checks(): unknown descriptor type=%d", seg->cache.type));
  }

  return 1;
}
