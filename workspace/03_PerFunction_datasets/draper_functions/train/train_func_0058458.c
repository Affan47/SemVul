ubh_bforget (struct ufs_buffer_head * ubh)
{
	unsigned i;
	if (!ubh)
		return;
	for ( i = 0; i < ubh->count; i++ ) if ( ubh->bh[i] )
		bforget (ubh->bh[i]);
}
