gar_rect_contains(struct gar_rect *r1, double lat, double lon)
{
	int ret = 0;


	if (r1->lulat >= lat && lat >= r1->rllat)
		ret = 3;

	if (r1->lulong <= lon && lon <= r1->rllong)
		ret ++;


#if 0
	if (ret !=4 ) {
		gar_rect_log(1,"rect", r1);
		log(1,"lat=%f, lon=%f, ret=%d\n", lat, lon, ret);
		if (r1->lulong <= lon)
			log(1, "lulong %f <= lon %f\n", r1->lulong, lon);
		if (r1->lulong >= lon)
			log(1, "lulong %f >= lon %f\n", r1->lulong, lon);
		if (r1->rllong <= lon)
			log(1, "rllong %f <= lon %f\n", r1->rllong, lon);
		if (r1->rllong >= lon)
			log(1, "rllong %f >= lon %f\n", r1->rllong, lon);


	} else {
		gar_rect_log(1,"contains rect", r1);
	}
#endif
	return ret ==  4;
}
