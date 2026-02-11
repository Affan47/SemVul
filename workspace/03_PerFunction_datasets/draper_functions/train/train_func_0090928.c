indent(int change)
{
    if (change > 0) {
        for (int i = 0; i < change; ++i)
            mEndline[mPadding + i + 1] = ' ';
    }
    mPadding += change;
    mEndline[mPadding + 1] = '\0';
}
