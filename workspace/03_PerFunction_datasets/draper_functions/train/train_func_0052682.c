IsEOLSkip(StyleContext &sc)
{

    if (sc.ch == '\r' && sc.chNext == '\n')
    {

        sc.Forward();
        return true;
    }


    return IsEOL(sc.ch, sc.chNext);
}
