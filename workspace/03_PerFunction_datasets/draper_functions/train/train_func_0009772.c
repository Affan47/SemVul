ispunctuation(int c) {
	char *p=".{}[],.;*+-=!&/|():?<>%^";
	for(;*p;p++) { if(c==*p) return 1; }
	return 0;
}
