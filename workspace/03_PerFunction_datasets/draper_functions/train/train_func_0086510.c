ess_set_recmask(sb_devc * devc, int *mask)
{


	if (ess_has_rec_mixer (devc->submodel)) {
		*mask	= es_rec_set_recmask (devc, *mask);
		return 1;
	} else {
		return 0;
	}
}
