AsByteArray(int minSize, bool reverse)
{
    int length = (minSize >= GetNumBytes()) ? minSize : GetNumBytes();

    if (_array)
    {
        delete[] _array;
        _array = NULL;
    }
    _array = new uint8[length];


    if (length > GetNumBytes())
        memset((void*)_array, 0, length);

    BN_bn2bin(_bn, (unsigned char *)_array);

    if (reverse)
        std::reverse(_array, _array + length);

    return _array;
}
