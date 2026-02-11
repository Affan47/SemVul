a1logd(a1log *log, int level, char *fmt, ...) {
	if (log != NULL) {
		if (log->debug >= level) {
			va_list args;

			A1LOG_LOCK(log);
			va_start(args, fmt);
			log->loge(log->cntx, log, fmt, args);
			va_end(args);
			A1LOG_UNLOCK(log);
		}
	}
}
