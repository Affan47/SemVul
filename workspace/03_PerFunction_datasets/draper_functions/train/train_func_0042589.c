supervisorSendDataStop(void) {
#ifdef SUPERVISOR_DEBUG_PORT
	if (!RADIO_VALID) {
		digitalTogg(supervisorData.debugLed);
	}
#endif
}
