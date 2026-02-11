buffer_complete(struct urb *urb)
{
	struct pvr2_buffer *bp = urb->context;
	struct pvr2_stream *sp;
	unsigned long irq_flags;
	BUFFER_CHECK(bp);
	sp = bp->stream;
	bp->used_count = 0;
	bp->status = 0;
	pvr2_trace(PVR2_TRACE_BUF_FLOW,
		   "/*---TRACE_FLOW---*/ bufferComplete %p stat=%d cnt=%d",
		   bp,urb->status,urb->actual_length);
	spin_lock_irqsave(&sp->list_lock,irq_flags);
	if ((!(urb->status)) ||
	    (urb->status == -ENOENT) ||
	    (urb->status == -ECONNRESET) ||
	    (urb->status == -ESHUTDOWN)) {
		(sp->buffers_processed)++;
		sp->bytes_processed += urb->actual_length;
		bp->used_count = urb->actual_length;
		if (sp->fail_count) {
			pvr2_trace(PVR2_TRACE_TOLERANCE,
				   "stream %p transfer ok"
				   " - fail count reset",sp);
			sp->fail_count = 0;
		}
	} else if (sp->fail_count < sp->fail_tolerance) {


		(sp->fail_count)++;
		(sp->buffers_failed)++;
		pvr2_trace(PVR2_TRACE_TOLERANCE,
			   "stream %p ignoring error %d"
			   " - fail count increased to %u",
			   sp,urb->status,sp->fail_count);
	} else {
		(sp->buffers_failed)++;
		bp->status = urb->status;
	}
	spin_unlock_irqrestore(&sp->list_lock,irq_flags);
	pvr2_buffer_set_ready(bp);
	if (sp && sp->callback_func) {
		sp->callback_func(sp->callback_data);
	}
}
