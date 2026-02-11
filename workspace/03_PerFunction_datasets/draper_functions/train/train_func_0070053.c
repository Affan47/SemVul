sec_to_pub_keyblock(KBNODE sec_keyblock)
{
  KBNODE secnode,pub_keyblock=NULL,ctx=NULL;

  while((secnode=walk_kbnode(sec_keyblock,&ctx,0)))
    {
      KBNODE pubnode;

      if(secnode->pkt->pkttype==PKT_SECRET_KEY ||
	 secnode->pkt->pkttype==PKT_SECRET_SUBKEY)
	{


	  PKT_secret_key *sk=secnode->pkt->pkt.secret_key;
	  PACKET *pkt=xmalloc_clear(sizeof(PACKET));
	  PKT_public_key *pk=xmalloc_clear(sizeof(PKT_public_key));
	  int n;

	  if(secnode->pkt->pkttype==PKT_SECRET_KEY)
	    pkt->pkttype=PKT_PUBLIC_KEY;
	  else
	    pkt->pkttype=PKT_PUBLIC_SUBKEY;

	  pkt->pkt.public_key=pk;

	  pk->version=sk->version;
	  pk->timestamp=sk->timestamp;
	  pk->expiredate=sk->expiredate;
	  pk->pubkey_algo=sk->pubkey_algo;

	  n=pubkey_get_npkey(pk->pubkey_algo);
	  if(n==0)
	    {


	      release_kbnode(pub_keyblock);
	      return NULL;
	    }
	  else
	    {
	      int i;

	      for(i=0;i<n;i++)
		pk->pkey[i]=mpi_copy(sk->skey[i]);
	    }

	  pubnode=new_kbnode(pkt);
	}
      else
	{
	  pubnode=clone_kbnode(secnode);
	}

      if(pub_keyblock==NULL)
	pub_keyblock=pubnode;
      else
	add_kbnode(pub_keyblock,pubnode);
    }

  return pub_keyblock;
}
