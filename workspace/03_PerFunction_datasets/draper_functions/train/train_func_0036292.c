clnttcp_control (CLIENT *cl, int request, char *info)
{
  struct ct_data *ct = (struct ct_data *) cl->cl_private;
  u_long ul;
  u_int32_t ui32;


  switch (request)
    {
    case CLSET_FD_CLOSE:
      ct->ct_closeit = TRUE;
      break;
    case CLSET_FD_NCLOSE:
      ct->ct_closeit = FALSE;
      break;
    case CLSET_TIMEOUT:
      ct->ct_wait = *(struct timeval *) info;
      ct->ct_waitset = TRUE;
      break;
    case CLGET_TIMEOUT:
      *(struct timeval *) info = ct->ct_wait;
      break;
    case CLGET_SERVER_ADDR:
      *(struct sockaddr_in *) info = ct->ct_addr;
      break;
    case CLGET_FD:
      *(int *)info = ct->ct_sock;
      break;
    case CLGET_XID:


      memcpy (&ui32, ct->ct_mcall, sizeof (ui32));
      ul = ntohl (ui32);
      memcpy (info, &ul, sizeof (ul));
      break;
    case CLSET_XID:

      memcpy (&ul, info, sizeof (ul));
      ui32 = htonl (ul - 1);
      memcpy (ct->ct_mcall, &ui32, sizeof (ui32));

      break;
    case CLGET_VERS:


      memcpy (&ui32, ct->ct_mcall + 4 * BYTES_PER_XDR_UNIT, sizeof (ui32));
      ul = ntohl (ui32);
      memcpy (info, &ul, sizeof (ul));
      break;
    case CLSET_VERS:
      memcpy (&ul, info, sizeof (ul));
      ui32 = htonl (ul);
      memcpy (ct->ct_mcall + 4 * BYTES_PER_XDR_UNIT, &ui32, sizeof (ui32));
      break;
    case CLGET_PROG:


      memcpy (&ui32, ct->ct_mcall + 3 * BYTES_PER_XDR_UNIT, sizeof (ui32));
      ul = ntohl (ui32);
      memcpy (info, &ul, sizeof (ul));
      break;
    case CLSET_PROG:
      memcpy (&ul, info, sizeof (ul));
      ui32 = htonl (ul);
      memcpy (ct->ct_mcall + 3 * BYTES_PER_XDR_UNIT, &ui32, sizeof (ui32));
      break;

    case CLGET_RETRY_TIMEOUT:
    case CLSET_RETRY_TIMEOUT:
    case CLGET_SVC_ADDR:
    case CLSET_SVC_ADDR:
    case CLSET_PUSH_TIMOD:
    case CLSET_POP_TIMOD:
    default:
      return FALSE;
    }
  return TRUE;
}
