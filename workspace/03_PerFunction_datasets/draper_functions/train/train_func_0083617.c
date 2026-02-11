keyInput(s8 *buf, u32 len)
{
	if (mImProxy && mImProxy->actived()) {
		mImProxy->sendKey(buf, len);
	} else {
		imInput(buf, len);
	}
}
