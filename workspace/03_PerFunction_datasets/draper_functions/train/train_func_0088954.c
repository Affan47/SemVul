pidWords(PID p) {
	const char* twd[] = {"gamma","beta","muon","LED","BiPulser"};
	if(p<=PID_PULSER) return twd[p];
	return "unknown";
}
