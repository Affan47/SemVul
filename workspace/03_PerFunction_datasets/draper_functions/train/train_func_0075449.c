SetOutStreamSize(const UInt64 *outSize)
{
    if ((_outSizeDefined = (outSize != NULL)))
	_outSize = *outSize;
    _remainLen = kLenIdNeedInit;
    _outWindowStream.Init();
    return S_OK;
}
