vending_vendinglistreq(struct map_session_data *sd, int id)
{
	struct map_session_data *vsd;

	nullpo_retv(sd);

	if( (vsd = map_id2sd(id)) == NULL )
		return;
	if( vsd->bl.prev == NULL )
		return;
	if( vsd->state.store != STORE_TYPE_VENDING )
		return;
	if( sd->state.store )
		return;
	if( vsd->state.deal_mode != 0 || sd->state.deal_mode != 0 )
	{
		clif_buyvending(sd, 0, 0, VENDING_FAIL_TRADING);
		return;
	}
	if( sd->bl.m != vsd->bl.m )
		return;
	if( path_distance(sd->bl.x,sd->bl.y,vsd->bl.x,vsd->bl.y) > AREA_SIZE )
		return;

	clif_vendinglist(sd, vsd);

	return;
}
