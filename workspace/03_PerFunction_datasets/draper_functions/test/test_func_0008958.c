ipmi_lan_check_net_fn (fiid_obj_t obj_lan_msg_hdr, uint8_t net_fn)
{
  uint8_t net_fn_recv;
  uint64_t val;

  if (!fiid_obj_valid (obj_lan_msg_hdr)
      || !IPMI_NET_FN_VALID (net_fn))
    {
      SET_ERRNO (EINVAL);
      return (-1);
    }

  if (FIID_OBJ_FIELD_LOOKUP (obj_lan_msg_hdr, "net_fn") < 0)
    {
      FIID_OBJECT_ERROR_TO_ERRNO (obj_lan_msg_hdr);
      return (-1);
    }

  if (FIID_OBJ_GET (obj_lan_msg_hdr, "net_fn", &val) < 0)
    {
      FIID_OBJECT_ERROR_TO_ERRNO (obj_lan_msg_hdr);
      return (-1);
    }
  net_fn_recv = val;

  return ((net_fn_recv == net_fn) ? 1 : 0);
}
