sgen_drain_gray_stack (int max_objs, ScanCopyContext ctx)
{
	char *obj;
	ScanObjectFunc scan_func = ctx.scan_func;
	GrayQueue *queue = ctx.queue;

	if (max_objs == -1) {
		for (;;) {
			GRAY_OBJECT_DEQUEUE (queue, obj);
			if (!obj)
				return TRUE;
			SGEN_LOG (9, "Precise gray object scan %p (%s)", obj, safe_name (obj));
			scan_func (obj, queue);
		}
	} else {
		int i;

		do {
			for (i = 0; i != max_objs; ++i) {
				GRAY_OBJECT_DEQUEUE (queue, obj);
				if (!obj)
					return TRUE;
				SGEN_LOG (9, "Precise gray object scan %p (%s)", obj, safe_name (obj));
				scan_func (obj, queue);
			}
		} while (max_objs < 0);
		return FALSE;
	}
}
