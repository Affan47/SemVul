insert(const String &s, int pos)
{
	if (pos > mLength || pos < 0)
		throw MsgException("index out of bounds");
	if (!s.mLength) return;
	realloc(mLength+s.mLength);
	if (mLength-s.mLength-pos > 0)
		memmove(&mContent[pos+s.mLength], &mContent[pos], mLength-s.mLength-pos);
	memmove(&mContent[pos], s.mContent, s.mLength);
}
