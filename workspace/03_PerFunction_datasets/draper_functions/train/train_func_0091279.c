givehnsi(ptfig, index, ptins)
lofig_list		*ptfig;
int			index;
loins_list		*ptins;
{
	ptype_list	*ptl;
	struct hns_I	*headi, *scani;

	ptl = getptype(	ptfig->USER, HNSRCNI );
	if( !ptl ) {
		ptfig->USER = addptype( ptfig->USER, HNSRCNI, NULL );
		ptl = ptfig->USER;
	}
	headi = (struct hns_I*)(ptl->DATA);

	for( scani = headi; scani; scani = scani->NEXT ) {
		if (scani->idx == index && scani->ins == ptins)
			break;
	}

	if(!scani) {
		scani       = add_hns_I();
		scani->idx  = index;
		scani->NEXT = headi;
		scani->ins  = ptins;
		scani->rcn  = 0;
		headi       = scani;
		ptl->DATA   = headi;
	}

	return(scani);

}
