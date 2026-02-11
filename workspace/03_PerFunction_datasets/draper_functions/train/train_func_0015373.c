quarantine_cleanup(void *arg)
{
	quarantine_t *quarantine = *(quarantine_t **)arg;

	if (quarantine == QUARANTINE_STATE_REINCARNATED) {


		quarantine = QUARANTINE_STATE_PURGATORY;
		quarantine_tsd_set(&quarantine);
	} else if (quarantine == QUARANTINE_STATE_PURGATORY) {


	} else if (quarantine != NULL) {
		quarantine_drain(quarantine, 0);
		idalloc(quarantine);
		quarantine = QUARANTINE_STATE_PURGATORY;
		quarantine_tsd_set(&quarantine);
	}
}
