do_qr_summary(void)
{
	unsigned i;
	const char *comma = "";

	trace_ds("> QueryReply(Summary(");
	space3270out(NSR);
	for (i = 0; i < NSR; i++) {
#if defined(X3270_DBCS)
		if (dbcs || replies[i].code != QR_DBCS_ASIA) {
#endif
			trace_ds("%s%s", comma, see_qcode(replies[i].code));
			comma = ",";
			*obptr++ = replies[i].code;
#if defined(X3270_DBCS)
		}
#endif
	}
	trace_ds("))\n");
}
