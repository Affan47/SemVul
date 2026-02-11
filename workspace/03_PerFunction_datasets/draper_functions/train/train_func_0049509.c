zGetDurationIsochoreGroup(const zDurationGroup *dm, float gc){
	 int iso_group=-1;


	int i;

	if(iso_group == -1){
		iso_group = 0;
		if(dm->durations > 1){
			for(i = 0; i < dm->durations; i++){
				if(gc < dm->iso_bound[i]){
					iso_group=i;
					break;
				}
			}
		}
	}

	return iso_group;
}
