index_is_within_range(index_t* meta, double ra, double dec, double radius_deg) {
	if (meta->healpix == -1) {

		return TRUE;
	}
	return (healpix_distance_to_radec(meta->healpix, meta->hpnside, ra, dec, NULL) <= radius_deg);
}
