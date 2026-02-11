ahd_assert_modes(struct ahd_softc *ahd, ahd_mode srcmode,
		 ahd_mode dstmode, const char *file, int line)
{
#ifdef AHD_DEBUG
	if ((srcmode & AHD_MK_MSK(ahd->src_mode)) == 0
	 || (dstmode & AHD_MK_MSK(ahd->dst_mode)) == 0) {
		panic("%s:%s:%d: Mode assertion failed.\n",
		       ahd_name(ahd), file, line);
	}
#endif
}
