CMoptPrintList (CMmsgType msgType, const char *optName, const char *choices []) {
	int i;
	CMmsgPrint (msgType,"Help [%s] options:",optName);
	for (i = 0;choices [i] != (char *) NULL;++i) CMmsgPrint (msgType," %s",choices [i]);
	CMmsgPrint (msgType,"\n");
}
