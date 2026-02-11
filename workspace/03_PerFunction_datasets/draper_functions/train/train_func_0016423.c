debrief_multi_fixup_stages()
{
	int i;


	if ( Badge_bitmap >= 0 ) {

		for ( i = Num_debrief_stages; i > 0; i-- ) {
			Debrief_stages[i] = Debrief_stages[i-1];
		}
		Debrief_stages[0] = &Badge_stage;
		Num_debrief_stages++;
	}

	if ( Promoted >= 0) {

		for ( i = Num_debrief_stages; i > 0; i-- ) {
			Debrief_stages[i] = Debrief_stages[i-1];
		}
		Debrief_stages[0] = &Promotion_stage;
		Num_debrief_stages++;
	}
}
