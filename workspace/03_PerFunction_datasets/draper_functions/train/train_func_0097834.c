replay(int which, threadinfo *ti)
{
    waituntilphase(REC_LOG_TS);

    if (buf_) {
	info_type x = info();
	pthread_mutex_lock(&rec_mu);
	rec_log_infos[which] = x;
	pthread_mutex_unlock(&rec_mu);
    }
    inactive();

    waituntilphase(REC_LOG_ANALYZE_WAKE);
    if (buf_) {
        if (rec_replay_min_quiescent_last_epoch
            && rec_replay_min_quiescent_last_epoch <= rec_log_infos[which].wake_epoch)
            rec_log_infos[which].min_post_quiescent_wake_epoch =
                min_post_quiescent_wake_epoch(rec_replay_min_quiescent_last_epoch);
    }
    inactive();

    waituntilphase(REC_LOG_REPLAY);
    if (buf_) {
	ti->rcu_start();
	uint64_t nr = replayandclean1(rec_replay_min_epoch, rec_replay_max_epoch, ti);
	ti->rcu_stop();
	printf("recovered %" PRIu64 " records from %s\n", nr, filename_.c_str());
    }
    inactive();
}
