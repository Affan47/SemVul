get_netbios_ssn (decode_proto_t *dp)
{
#define SESSION_MESSAGE 0
  guint8 mesg_type;

  decode_proto_add(dp, "NETBIOS-SSN");

  mesg_type = dp->cur_packet[0];

  if (mesg_type == SESSION_MESSAGE)
    decode_proto_add(dp, "SMB");


}
