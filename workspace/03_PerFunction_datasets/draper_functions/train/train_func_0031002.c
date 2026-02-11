gf_smil_timing_get_interval_end(SMIL_Timing_RTI *rti, SMIL_Interval *interval)
{
	u32 end_count, j;


	interval->end = -2;

	end_count = (rti->timingp->end ? gf_list_count(*rti->timingp->end) : 0);

	if (end_count > 0) {
		for (j = 0; j < end_count; j++) {
			SMIL_Time *end = (SMIL_Time*)gf_list_get(*rti->timingp->end, j);
			if ( GF_SMIL_TIME_IS_CLOCK(end->type) )  {
				if( end->clock >= interval->begin) {
					interval->end = end->clock;
					break;
				}
			} else {

				interval->end = -1;
				break;
			}
		}
	} else {
		interval->end = -1;
	}
}
