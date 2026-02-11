bitmap() const
{
    if (_def) return _def->bitmap();
    if (_bitmapData) return _bitmapData->bitmapInfo();
    return 0;
}
