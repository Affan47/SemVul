IoObject_rawDoString_label_(IoObject *self, IoSymbol *string, IoSymbol *label)
{
	IoMessage *cm = NULL;
	IoMessage *messageForString = NULL;
	IoMessage *newMessage = NULL;
	IoState *state = IOSTATE;

	if(!ISSEQ(string))
	{
		IoState_error_(state, NULL, "IoObject_rawDoString_label_ requires a string argument");
	}

	{
		IoSymbol *internal;
		IoState_pushCollectorPause(state);

		internal = IOSYMBOL("[internal]");
		cm = IoMessage_newWithName_label_(state, IOSYMBOL("Compiler"), internal);
		messageForString = IoMessage_newWithName_label_(state, IOSYMBOL("messageForString"), internal);

		IoMessage_rawSetNext_(cm, messageForString);
		IoMessage_addCachedArg_(messageForString, string);
		IoMessage_addCachedArg_(messageForString, label);

		newMessage = IoMessage_locals_performOn_(cm, self, self);
		IoState_stackRetain_(state, newMessage);

		IoState_popCollectorPause(state);

		if (newMessage)
		{
			return IoMessage_locals_performOn_(newMessage, self, self);
		}

		IoState_error_(state, NULL, "no message compiled\n");
		return IONIL(self);
	}
}
