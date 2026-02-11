stun_strerror (StunError code)
{
  static const struct
  {
    StunError code;
    char     phrase[32];
  } tab[] =
  {
    { STUN_ERROR_TRY_ALTERNATE, "Try alternate server" },
    { STUN_ERROR_BAD_REQUEST, "Bad request" },
    { STUN_ERROR_UNAUTHORIZED, "Unauthorized" },
    { STUN_ERROR_UNKNOWN_ATTRIBUTE, "Unknown Attribute" },
    { STUN_ERROR_ALLOCATION_MISMATCH, "Allocation Mismatch" },
    { STUN_ERROR_STALE_NONCE, "Stale Nonce" },
    { STUN_ERROR_ACT_DST_ALREADY, "Active Destination Already Set" },
    { STUN_ERROR_UNSUPPORTED_FAMILY, "Address Family not Supported" },
    { STUN_ERROR_UNSUPPORTED_TRANSPORT, "Unsupported Transport Protocol" },
    { STUN_ERROR_INVALID_IP, "Invalid IP Address" },
    { STUN_ERROR_INVALID_PORT, "Invalid Port" },
    { STUN_ERROR_OP_TCP_ONLY, "Operation for TCP Only" },
    { STUN_ERROR_CONN_ALREADY, "Connection Already Exists" },
    { STUN_ERROR_ALLOCATION_QUOTA_REACHED, "Allocation Quota Reached" },
    { STUN_ERROR_ROLE_CONFLICT, "Role conflict" },
    { STUN_ERROR_SERVER_ERROR, "Server Error" },
    { STUN_ERROR_SERVER_CAPACITY, "Insufficient Capacity" },
    { STUN_ERROR_INSUFFICIENT_CAPACITY, "Insufficient Capacity" },
  };
  const char *str = "Unknown error";
  size_t i;

  for (i = 0; i < (sizeof (tab) / sizeof (tab[0])); i++)
  {
    if (tab[i].code == code)
    {
      str = tab[i].phrase;
      break;
    }
  }


  return str;
}
