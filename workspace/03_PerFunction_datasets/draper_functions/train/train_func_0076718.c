ipmipower_check_payload_pad (ipmipower_powercmd_t ip, packet_type_t pkt)
{
  uint8_t confidentiality_algorithm;
  int rv;

  assert (ip);
  assert (PACKET_TYPE_VALID_RES (pkt));
  assert (cmd_args.common.driver_type == IPMI_DEVICE_LAN_2_0
          && (pkt == SET_SESSION_PRIVILEGE_LEVEL_RES
              || pkt == GET_CHASSIS_STATUS_RES
              || pkt == CHASSIS_CONTROL_RES
              || pkt == CHASSIS_IDENTIFY_RES
              || pkt == CLOSE_SESSION_RES));

  confidentiality_algorithm = ip->confidentiality_algorithm;

  if ((rv = ipmi_rmcpplus_check_payload_pad (confidentiality_algorithm,
                                             ip->obj_rmcpplus_payload_res)) < 0)
    {
      IPMIPOWER_ERROR (("ipmi_rmcpplus_check_payload_pad: %s", strerror (errno)));
      exit (1);
    }

  if (!rv)
    IPMIPOWER_DEBUG (("host = %s; p = %d; payload pad check failed",
                      ip->ic->hostname,
                      ip->protocol_state));

  return (rv);
}
