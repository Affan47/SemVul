ObeyProc(p)
void (*p) ptrproto((void));
{
	if (BufMinorMode(curbuf, ReadOnly)) {
		rbell();
		message("[Buffer is read-only]");
		return NO;
	} else {
		(*p)();
		return YES;
	}
}
