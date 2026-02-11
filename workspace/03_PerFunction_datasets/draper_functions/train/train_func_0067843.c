changeMode(ModeType type, u16 val)
{
	const s8 *str = 0;

	if (type == CursorKeyEscO) str = (val ? "\e[?1h" : "\e[?1l");
	else if (type == AutoRepeatKey) str = (val ? "\e[?8h" : "\e[?8l");
	else if (type == ApplicKeypad) str = (val ? "\e=" : "\e>");
	else if (type == CRWithLF) str = (val ? "\e[20h" : "\e[20l");

	if (str) {
		s32 ret = ::write(STDIN_FILENO, str, strlen(str));
	}
}
