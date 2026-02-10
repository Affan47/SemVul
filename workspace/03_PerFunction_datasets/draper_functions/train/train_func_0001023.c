writeEnableDebugger(char *str)
{
	if (strlen(str) == 0) {

		writeTagHeader(TAG_ENABLEDEBUGGER, 0);
	}
	else {

		writeTagHeader(TAG_ENABLEDEBUGGER, strlen(str) + 3);
		flputShort(0);
		flputString(str);
	}
}
