eraseMargin(bool top, u16 h)
{
	if (mWidth % FW(1)) {
		fillRect(FW(mCols), top ? 0 : FH(mRows - h), mWidth % FW(1), FH(h), 0);
	}

	if (mHeight % FH(1)) {
		fillRect(0, FH(mRows), mWidth, mHeight % FH(1), 0);
	}
}
