beam_unpause_sounds()
{
	beam *moveup = NULL;


	moveup = GET_FIRST(&Beam_used_list);
	if(moveup == NULL){
		return;
	}
	while(moveup != END_OF_LIST(&Beam_used_list)){
		beam_recalc_sounds(moveup);


		moveup = GET_NEXT(moveup);
	}
}
