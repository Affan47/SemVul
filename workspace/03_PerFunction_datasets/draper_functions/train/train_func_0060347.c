zStepPinArrayForward(zPinSearch* ps,zPinArrayData* from_pad){
	int            i,prestate,state;
	score_t        score;
	zIVec*         jumps;
	zHMM*          hmm = ps->trellis->hmm;


	zPinSearchResetTmp(ps);


	for(state = 0;state < ps->states;state++){
		if(hmm->state[state].type == INTERNAL ||
		   hmm->state[state].type == GINTERNAL){
			jumps = hmm->jmap[state];
			for(i = 0; i < jumps->size; i++) {
				prestate = jumps->elem[i];
				score = ps->data[from_pad->index][prestate].score;
				if(score == MIN_SCORE) continue;
				if(hmm->state[state].type == INTERNAL){
					score += zGetTransitionScore(ps->trellis->hmm,prestate,state,ps->trellis->tiso_group);
				}
				else{
					score += zGetIntergenicContinueScore(ps->trellis);
				}
				score += zScoreInternalState(ps->trellis,state,ps->end_pos,(state != prestate));
				if(score > ps->tmp[state].score){
					ps->tmp[state].score = score;
					ps->tmp[state].pinstate = ps->data[from_pad->index][prestate].pinstate;
				}
			}
		}
		else if(hmm->state[state].type == EXTERNAL){

		}
		else{
			zDie("zPinSearch only supports INTERNAL and EXTERNAL states");
		}
	}

	for(state = 0;state < ps->states;state++){
		ps->data[from_pad->index][state].score = ps->tmp[state].score;
		ps->data[from_pad->index][state].pinstate = ps->tmp[state].pinstate;
	}
}
