Write(trpgWriteBuffer &buf)
{
    if (!isValid())
        return false;


    int tok = TRPGMODELREF;
    if(writeHandle)
        tok = TRPGMODELREF2;


#ifdef OLDMODELSTYLE
    buf.Begin(tok);
    buf.Add(type);

    if(writeHandle) {
        buf.Add((int)handle);
    }
    if (name)
        buf.Add(name);
    else
        buf.Add(diskRef);
    buf.Add(useCount);

#else
    buf.Begin(tok);
    if(writeHandle) {
        buf.Add((int)handle);
    }
    buf.Add(type);
    buf.Add(name);
    buf.Add(diskRef);
    buf.Add(useCount);
#endif
    buf.End();

    return true;
}
