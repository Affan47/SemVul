H5Z_term_interface(void)
{
#ifdef H5Z_DEBUG
    size_t	i;
    int		dir, nprint=0;
    char	comment[16], bandwidth[32];
#endif

    if(H5_interface_initialize_g) {
#ifdef H5Z_DEBUG
	if (H5DEBUG(Z)) {
	    for (i=0; i<H5Z_table_used_g; i++) {
		for (dir=0; dir<2; dir++) {
		    if (0==H5Z_stat_table_g[i].stats[dir].total) continue;

		    if (0==nprint++) {

			HDfprintf (H5DEBUG(Z), "H5Z: filter statistics "
				   "accumulated over life of library:\n");
			HDfprintf (H5DEBUG(Z),
				   "   %-16s %10s %10s %8s %8s %8s %10s\n",
				   "Filter", "Total", "Errors", "User",
				   "System", "Elapsed", "Bandwidth");
			HDfprintf (H5DEBUG(Z),
				   "   %-16s %10s %10s %8s %8s %8s %10s\n",
				   "------", "-----", "------", "----",
				   "------", "-------", "---------");
		    }


		    HDstrncpy(comment, H5Z_table_g[i].name,
			      sizeof comment);
		    comment[sizeof(comment)-1] = '\0';


		    H5_bandwidth(bandwidth,
				 (double)(H5Z_stat_table_g[i].stats[dir].total),
				 H5Z_stat_table_g[i].stats[dir].timer.etime);


		    HDfprintf (H5DEBUG(Z),
			       "   %s%-15s %10Hd %10Hd %8.2f %8.2f %8.2f "
			       "%10s\n", dir?"<":">", comment,
			       H5Z_stat_table_g[i].stats[dir].total,
			       H5Z_stat_table_g[i].stats[dir].errors,
			       H5Z_stat_table_g[i].stats[dir].timer.utime,
			       H5Z_stat_table_g[i].stats[dir].timer.stime,
			       H5Z_stat_table_g[i].stats[dir].timer.etime,
			       bandwidth);
		}
	    }
	}
#endif

	H5Z_table_g = (H5Z_class2_t *)H5MM_xfree(H5Z_table_g);
#ifdef H5Z_DEBUG
	H5Z_stat_table_g = (H5Z_stats_t *)H5MM_xfree(H5Z_stat_table_g);
#endif
	H5Z_table_used_g = H5Z_table_alloc_g = 0;
	H5_interface_initialize_g = 0;
    }

    return(0);
}
