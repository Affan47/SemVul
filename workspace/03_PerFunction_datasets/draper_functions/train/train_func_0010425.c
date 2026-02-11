VSM_common_cleaner(struct vsm_sc *sc, struct VSC_C_main *stats)
{
	double now = VTIM_real();
	struct vsm_range *vr, *vr2;

	CHECK_OBJ_NOTNULL(sc, VSM_SC_MAGIC);


	VTAILQ_FOREACH_SAFE(vr, &sc->r_cooling, list, vr2) {
		if (vr->cool > now)
			break;
		VTAILQ_REMOVE(&sc->r_cooling, vr, list);
		vsm_common_insert_free(sc, vr);
	}
	stats->vsm_free = sc->g_free;
	stats->vsm_used = sc->g_used;
	stats->vsm_cooling = sc->g_cooling;
	stats->vsm_overflow = sc->g_overflow;
	stats->vsm_overflowed = sc->c_overflow;
}
