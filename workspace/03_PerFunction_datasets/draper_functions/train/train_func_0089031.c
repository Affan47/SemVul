IoRange_last(IoRange *self, IoObject *locals, IoMessage *m)
{


	IoRangeData *rd = DATA(self);
	IoObject *context;

	IoObject *v = IoObject_rawGetSlot_context_(rd->curr, IOSYMBOL("nextInSequence"), &context);
	IoObject *lt = IoObject_rawGetSlot_context_(rd->curr, IOSYMBOL("compare"), &context);

	if(v && lt)
	{
		IoObject *last, *result_lt;
		IoMessage *newMessage = IoMessage_new(IOSTATE);

		double index = ceil((CNUMBER(rd->end) - CNUMBER(rd->start))/CNUMBER(rd->increment)) - 1;
		IoMessage_setCachedArg_to_(newMessage, 0, IONUMBER(CNUMBER(rd->increment)*(index)));
		last = IoObject_activate(v, rd->start, locals, newMessage, context);


		IoRange_setCurrent(self, last);
		IoRange_setIndex(self, IONUMBER(index));


		IoMessage_setCachedArg_to_(newMessage, 0, rd->increment);
		last = IoObject_activate(v, rd->curr, locals, newMessage, context);

		IoMessage_setCachedArg_to_(newMessage, 0, rd->end);
		result_lt = IoObject_activate(lt, last, locals, newMessage, context);


		if(rd->end >= rd->start ? IoNumber_asInt(result_lt) <= 0 : IoNumber_asInt(result_lt) >= 0)
		{
			IoRange_setCurrent(self, last);
			IoRange_setIndex(self, IONUMBER(CNUMBER(rd->index) + 1));
		}
		return rd->curr;
	}
	return IONIL(self);
}
