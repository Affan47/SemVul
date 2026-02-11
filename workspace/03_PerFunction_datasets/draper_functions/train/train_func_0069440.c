toCBuffer2(OutBuffer *buf, HdrGenState *hgs, int mod)
{

    if (inuse)
    {   inuse = 2;
        return;
    }
    inuse++;

    functionToCBuffer2(this, buf, hgs, mod, "function");

    inuse--;
}
