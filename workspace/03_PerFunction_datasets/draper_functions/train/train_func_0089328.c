ivtv_vapi_result(struct ivtv *itv, u32 data[CX2341X_MBOX_MAX_DATA], int cmd, int args, ...)
{
	va_list ap;
	int i;

	va_start(ap, args);
	for (i = 0; i < args; i++) {
		data[i] = va_arg(ap, u32);
	}
	va_end(ap);
	return ivtv_api(itv, cmd, args, data);
}
