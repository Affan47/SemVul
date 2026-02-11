Read(trpgReadBuffer &buf)
{
    try {
        buf.Get(id);
        buf.Get(numRange);
        if (numRange < 0) throw 1;
        buf.Get(center);
        buf.Get(switchIn);
        buf.Get(switchOut);
        buf.Get(width);
        if ( !buf.isEmpty() ) {
            char nm[1024] = {0};
            buf.Get(nm,1024);
            if (*nm)
                SetName(nm);

            if (!buf.isEmpty())
                buf.Get(rangeIndex);
        }
    }
    catch (...) {
        return false;
    }

    return isValid();
}
