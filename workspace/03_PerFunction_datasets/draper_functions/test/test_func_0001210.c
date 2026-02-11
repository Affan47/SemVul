sayInteger(int value)
{
    char buf[25];

    if (isHere(HERO, FALSE)) {
        sprintf(buf, "%d", value);
        output(buf);
    }
}
