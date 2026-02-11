skipEOL()
{
    if ((mSource[mCharPos] == '\n') || (mSource[mCharPos] == '\r')) {
        mCurrentLine++;
        mCharPos++;
        if ((mSource[mCharPos] == '\n') || (mSource[mCharPos] == '\r')) {
            mCharPos++;
        }
    }
}
