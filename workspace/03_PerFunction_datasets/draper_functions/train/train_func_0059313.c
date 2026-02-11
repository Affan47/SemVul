enable_disable_key( KBNODE keyblock, int disable )
{
    PKT_public_key *pk = find_kbnode( keyblock, PKT_PUBLIC_KEY )
			    ->pkt->pkt.public_key;
    unsigned int trust, newtrust;

    trust = newtrust = get_ownertrust (pk);
    newtrust &= ~TRUST_FLAG_DISABLED;
    if( disable )
	newtrust |= TRUST_FLAG_DISABLED;
    if( trust == newtrust )
	return 0;
    update_ownertrust(pk, newtrust );
    return 0;
}
