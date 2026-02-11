vlreply(int code, const char* fmt, va_list ap)
{
    if (IS(LREPLIES)) {
	fxStackBuffer buf;
	buf.vput(fmt, ap);
	printf("%d-%.*s\r\n", code, buf.getLength(), (const char*) buf);
	fflush(stdout);

	if (TRACE(PROTOCOL))
	    logDebug("<--- %d-%.*s", code, buf.getLength(), (const char*) buf);
    }
}
