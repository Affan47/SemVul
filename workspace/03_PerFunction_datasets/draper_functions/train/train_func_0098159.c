hb_ot_old_tag_to_script (hb_tag_t tag)
{
  if (unlikely (tag == HB_OT_TAG_DEFAULT_SCRIPT))
    return HB_SCRIPT_INVALID;


  if (unlikely ((tag & 0x0000FF00) == 0x00002000))
    tag |= (tag >> 8) & 0x0000FF00;
  if (unlikely ((tag & 0x000000FF) == 0x00000020))
    tag |= (tag >> 8) & 0x000000FF;


  return (hb_script_t) (tag & ~0x20000000);
}
