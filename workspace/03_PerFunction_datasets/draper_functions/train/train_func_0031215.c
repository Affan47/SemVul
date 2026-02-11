get_ioa_socket_from_reservation(ioa_engine_handle e, u64bits in_reservation_token, ioa_socket_handle *s, u08bits *realm)
{
  if (e && in_reservation_token && s) {
    *s = rtcp_map_get(e->map_rtcp, in_reservation_token, realm);
    if (*s) {
      return 0;
    }
  }
  return -1;
}
