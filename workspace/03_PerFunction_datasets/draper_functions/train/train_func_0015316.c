update_sec_keyblock_with_cardinfo (KBNODE sec_keyblock,
                                   const unsigned char *fpr1,
                                   const unsigned char *fpr2,
                                   const unsigned char *fpr3,
                                   const char *serialnostr)
{
  KBNODE node;
  KBNODE walkctx = NULL;
  PKT_secret_key *sk;
  byte array[MAX_FINGERPRINT_LEN];
  size_t n;
  int result = 0;
  const char *s;

  while((node = walk_kbnode (sec_keyblock, &walkctx, 0)))
    {
      if (node->pkt->pkttype != PKT_SECRET_KEY
          && node->pkt->pkttype != PKT_SECRET_SUBKEY)
        continue;
      sk = node->pkt->pkt.secret_key;

      fingerprint_from_sk (sk, array, &n);
      if (n != 20)
        continue;
      if ( !((fpr1 && !memcmp (array, fpr1, 20))
             || (fpr2 && !memcmp (array, fpr2, 20))
             || (fpr3 && !memcmp (array, fpr3, 20))) )
        continue;

      if (sk->is_protected == 1 && sk->protect.s2k.mode == 1001)
        {

          sk->protect.s2k.mode = 1002;
          s = serialnostr;
          for (sk->protect.ivlen=0; sk->protect.ivlen < 16 && *s && s[1];
               sk->protect.ivlen++, s += 2)
            sk->protect.iv[sk->protect.ivlen] = xtoi_2 (s);
          result = 1;
        }
      else if (sk->is_protected == 1 && sk->protect.s2k.mode == 1002)
        {
          s = serialnostr;
          for (sk->protect.ivlen=0; sk->protect.ivlen < 16 && *s && s[1];
               sk->protect.ivlen++, s += 2)
            if (sk->protect.iv[sk->protect.ivlen] != xtoi_2 (s))
              {
                log_info (_("NOTE: a key's S/N does not "
                            "match the card's one\n"));
                break;
              }
        }
      else
        {
          if (node->pkt->pkttype != PKT_SECRET_KEY)
            log_info (_("NOTE: primary key is online and stored on card\n"));
          else
            log_info (_("NOTE: secondary key is online and stored on card\n"));
        }
    }

  return result;
}
