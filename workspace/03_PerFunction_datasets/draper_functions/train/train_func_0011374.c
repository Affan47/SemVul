h_hist(void *priv, enum VSL_tag_e tag, unsigned fd, unsigned len,
    unsigned spec, const char *ptr, uint64_t bm)
{
	double b;
	int i, j;
	struct VSM_data *vd = priv;

	(void)len;
	(void)spec;

	if (fd >= FD_SETSIZE)

		return (0);

	bitmap[fd] |= bm;

	if (tag == SLT_Hit) {
		hh[fd] = 1;
		return (0);
	}
	if (tag != SLT_ReqEnd)
		return (0);

	if (!VSL_Matched(vd, bitmap[fd])) {
		bitmap[fd] = 0;
		hh[fd] = 0;
		return (0);
	}


#if 1
	i = sscanf(ptr, "%*d %*f %*f %*f %lf", &b);
#else
	i = sscanf(ptr, "%*d %*f %*f %lf", &b);
#endif
	assert(i == 1);


	i = HIST_RES * (log(b) / log_ten);
	if (i < HIST_LOW * HIST_RES)
		i = HIST_LOW * HIST_RES;
	if (i >= HIST_HIGH * HIST_RES)
		i = HIST_HIGH * HIST_RES - 1;
	i -= HIST_LOW * HIST_RES;
	assert(i >= 0);
	assert(i < HIST_BUCKETS);

	pthread_mutex_lock(&mtx);


	if (nhist == HIST_N) {
		j = rr_hist[next_hist];
		if (j < 0)  {
			assert(bucket_miss[-j] > 0);
			bucket_miss[-j]--;
		} else {
			assert(bucket_hit[j] > 0);
			bucket_hit[j]--;
		}
	} else {
		++nhist;
	}


	if (hh[fd] || i == 0) {
		bucket_hit[i]++;
		rr_hist[next_hist] = i;
	} else {
		bucket_miss[i]++;
		rr_hist[next_hist] = -i;
	}
	if (++next_hist == HIST_N) {
		next_hist = 0;
	}
	hh[fd] = 0;
	bitmap[fd] = 0;

	pthread_mutex_unlock(&mtx);

	return (0);
}
