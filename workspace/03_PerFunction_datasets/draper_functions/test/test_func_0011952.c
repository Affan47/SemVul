iax2_allow_new(int frametype, int subclass, int inbound)
{
	if (frametype != AST_FRAME_IAX) {
		return 0;
	}
	switch (subclass) {
	case IAX_COMMAND_NEW:
	case IAX_COMMAND_REGREQ:
	case IAX_COMMAND_FWDOWNL:
	case IAX_COMMAND_REGREL:
		return 1;
	case IAX_COMMAND_POKE:
		if (!inbound) {
			return 1;
		}
		break;
	}
	return 0;
}
