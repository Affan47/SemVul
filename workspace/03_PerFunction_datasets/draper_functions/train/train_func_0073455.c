print_and_check_one_sig_colon( KBNODE keyblock, KBNODE node,
			       int *inv_sigs, int *no_key, int *oth_err,
			       int *is_selfsig, int print_without_key )
{
  PKT_signature *sig = node->pkt->pkt.signature;
  int rc, sigrc;


  switch((rc=check_key_signature(keyblock,node,is_selfsig)))
    {
    case 0:
      node->flag &= ~(NODFLG_BADSIG|NODFLG_NOKEY|NODFLG_SIGERR);
      sigrc = '!';
      break;
    case G10ERR_BAD_SIGN:
      node->flag = NODFLG_BADSIG;
      sigrc = '-';
      if( inv_sigs )
	++*inv_sigs;
      break;
    case G10ERR_NO_PUBKEY:
    case G10ERR_UNU_PUBKEY:
      node->flag = NODFLG_NOKEY;
      sigrc = '?';
      if( no_key )
	++*no_key;
      break;
    default:
      node->flag = NODFLG_SIGERR;
      sigrc = '%';
      if( oth_err )
	++*oth_err;
      break;
    }

  if( sigrc != '?' || print_without_key )
    {
      printf("sig:%c::%d:%08lX%08lX:%lu:%lu:",
	     sigrc,sig->pubkey_algo,(ulong)sig->keyid[0],(ulong)sig->keyid[1],
	     (ulong)sig->timestamp,(ulong)sig->expiredate);

      if(sig->trust_depth || sig->trust_value)
	printf("%d %d",sig->trust_depth,sig->trust_value);

      printf(":");

      if(sig->trust_regexp)
	print_string(stdout,sig->trust_regexp,strlen(sig->trust_regexp),':');

      printf("::%02x%c\n",sig->sig_class,sig->flags.exportable?'x':'l');

      if(opt.show_subpackets)
      	print_subpackets_colon(sig);
    }

  return (sigrc == '!');
}
