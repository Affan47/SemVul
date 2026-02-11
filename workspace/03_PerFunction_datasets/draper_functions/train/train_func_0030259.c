PrintASFMainHeader(const ASFMainHeader* h)
{
    char b[64];
    char sec1970str[128];
    struct tm result;

    time_t sec1970 = (int64_t) (h->create_time / 10000000) - SECS_1601_TO_1970;
#ifdef HAVE_LOCALTIME_R
    localtime_r(&sec1970, &result);
#else
    struct tm* r = localtime(&sec1970);
    memcpy(&result, r, sizeof(result));
#endif

#ifdef HAVE_ASCTIME_R
#ifdef HAVE_ASCTIME_R_LONG
    asctime_r(&result, sec1970str, sizeof(sec1970str) - 1);
#else
    asctime_r(&result, sec1970str);
#endif
#else
    char* bb = asctime(&result);
    strcpy(sec1970str, bb);
#endif
    char* d = strchr(sec1970str, '\n'); if (d) *d = 0;
    AVM_WRITE("ASF reader", "MainHeader: %s\n"
	      " Created: %s   File size=%.0f   Packets=%.0f\n"
	      " Total time=%.1f sec   Play time=%.1f sec   Preroll=%.1f sec\n"
	      " Flags=0x%x  Packet size=%d  (=%d)  MaxBandwidth=%d bps\n",
	      guid_to_string(b, &h->guid),
	      sec1970str,
	      (double)h->file_size,
	      (double)h->pkts_count,
	      (double)h->play_time / 10000000.,
	      (double)h->send_time / 10000000.,
	      (double)h->preroll / 1000., h->flags,
	      h->min_pktsize, h->max_pktsize,
	      h->max_bitrate);
}
