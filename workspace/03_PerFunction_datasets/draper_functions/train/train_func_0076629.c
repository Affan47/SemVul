TextMoveDown(int top, int btm, int line)
{
    u_int	n, src, dst;

    if (btm - top - line + 1 <= 0) {
	TextClearBand(top, btm);
	return;
    }
    for (n = btm; n >= top + line; n --) {
	dst = TextAddress(0, n);
	src = TextAddress(0, n - line);
	memcpy(textBuff + dst, textBuff + src, dInfo.glineByte);
	memcpy(attrBuff + dst, attrBuff + src, dInfo.glineByte);
	memcpy(flagBuff + dst, flagBuff + src, dInfo.glineByte);
	llatch(flagBuff + dst, dInfo.glineByte);
    }
    TextClearBand(top, top + line - 1);
}
