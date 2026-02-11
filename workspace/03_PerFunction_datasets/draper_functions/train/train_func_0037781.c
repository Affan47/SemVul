fs_network_protocol_to_nice_candidate_protocol (FsNetworkProtocol proto)
{
  switch (proto)
  {
    case FS_NETWORK_PROTOCOL_UDP:
      return NICE_CANDIDATE_TRANSPORT_UDP;
    default:
      GST_WARNING ("Invalid Fs network protocol type %u", proto);
      return NICE_CANDIDATE_TRANSPORT_UDP;
  }
}
