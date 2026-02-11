_ByteSwapIfNeeded (u32 D, unsigned ByteOrder)

{

    switch (ByteOrder) {
        case boLittleEndian:    return D;
        default:                return _ByteSwap (D);
    }
}
