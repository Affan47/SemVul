IoMessage_locals_performOn_(IoMessage *self, IoObject *locals, IoObject *target)
{
	IoState *state = IOSTATE;
	IoMessage *m = self;
	IoObject *result = target;
	IoObject *cachedTarget = target;


	IoMessageData *md;

	if (state->receivedSignal)
	{
		IoState_callUserInterruptHandler(IOSTATE);
	}

	do
	{


		if(state->showAllMessages)
		{
			printf("M:%s:%s:%i\n", CSTRING(IoMessage_name(m)), CSTRING(IoMessage_rawLabel(m)), IoMessage_rawLineNumber(m));
		}

		md = DATA(m);

		if(md->name == state->semicolonSymbol)
		{
			target = cachedTarget;
		}
		else
		{
			result = md->cachedResult;


			if (!result)
			{
				IoState_pushRetainPool(state);
#ifdef IOMESSAGE_INLINE_PERFORM
				if(IoObject_tag(target)->performFunc == NULL)
				{
					result = IoObject_perform(target, locals, m);
				}
				else
				{
					result = IoObject_tag(target)->performFunc(target, locals, m);
				}
#else
				result = IoObject_tag(target)->performFunc(target, locals, m);
#endif
				IoState_popRetainPoolExceptFor_(state, result);
			}


			target = result;

			if (state->stopStatus != MESSAGE_STOP_STATUS_NORMAL)
			{
					return state->returnValue;


			}
		}
	} while ((m = md->next));

	return result;
}
