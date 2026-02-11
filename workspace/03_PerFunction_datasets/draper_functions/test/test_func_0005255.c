Read(trpgReadBuffer &buf)
{
    try {
        buf.Get(numChild);
        buf.Get(id);
        if (id < 0)  throw 1;
        buf.Get(parentID);
        if (parentID < 0) throw 1;
        buf.Get(childPos);
        if (childPos < 0) throw 1;
        if ( !buf.isEmpty() ) {
            char nm[1024] = {0};
            buf.Get(nm,1024);
            SetName(nm);
        }
    }
    catch (...) {
        return false;
    }

    return true;
}
