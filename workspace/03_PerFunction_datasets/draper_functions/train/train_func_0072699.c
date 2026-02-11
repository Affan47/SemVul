get_rpc (decode_proto_t *dp, gboolean is_udp)
{
  int rpcstart;
  uint32_t rpcver;
  enum rpc_type msg_type;
  enum rpc_program msg_program;
  const gchar *rpc_prot = NULL;


  if (dp->cur_len < 24)
    return FALSE;

  if (is_udp)
    rpcstart = 0;
  else
    rpcstart = 4;

  msg_type = pntohl (dp->cur_packet + rpcstart + 4);

  switch (msg_type)
    {
    case RPC_REPLY:


      if (!(rpc_prot = find_conversation (&dp->global_dst_address,
                                          &dp->global_dst_address,
					  dp->global_dst_port, 0)))
	return FALSE;
      decode_proto_add(dp, "ONC-RPC");
      decode_proto_add(dp, rpc_prot);
      return TRUE;

    case RPC_CALL:
      rpcver = pntohl (dp->cur_packet + rpcstart + 8);
      if (rpcver != 2)
        return FALSE;

      msg_program = pntohl (dp->cur_packet + rpcstart + 12);
      switch (msg_program)
	{
	case BOOTPARAMS_PROGRAM:
	  rpc_prot = "BOOTPARAMS";
	  break;
	case MOUNT_PROGRAM:
	  rpc_prot = "MOUNT";
	  break;
	case NLM_PROGRAM:
	  rpc_prot = "NLM";
	  break;
	case PORTMAP_PROGRAM:
	  rpc_prot = "PORTMAP";
	  break;
	case STAT_PROGRAM:
	  rpc_prot = "STAT";
	  break;
	case NFS_PROGRAM:
	  rpc_prot = "NFS";
	  break;
	case YPBIND_PROGRAM:
	  rpc_prot = "YPBIND";
	  break;
	case YPSERV_PROGRAM:
	  rpc_prot = "YPSERV";
	  break;
	case YPXFR_PROGRAM:
	  rpc_prot = "YPXFR";
	  break;
	case YPPASSWD_PROGRAM:
	  rpc_prot = "YPPASSWD";
	  break;
	case REXEC_PROGRAM:
	  rpc_prot = "REXEC";
	  break;
	case KERBPROG_PROGRAM:
	  rpc_prot = "KERBPROG";
	  break;
	default:
          if (msg_program >= 100000 && msg_program <= 101999)
            rpc_prot = "RPC-UNKNOWN";
          else
            return FALSE;
          break;
	}


      g_assert(rpc_prot);
      if (!find_conversation (&dp->global_src_address, &dp->global_src_address, dp->global_src_port, 0))
	add_conversation (&dp->global_src_address, &dp->global_src_address,
			  dp->global_src_port, 0, rpc_prot);

      decode_proto_add(dp, "ONC-RPC");
      decode_proto_add(dp, rpc_prot);
      return TRUE;

    default:
      return FALSE;
    }

  return FALSE;
}
