warnOnce(bool & haveWarned, const format & f)
{
    if (!haveWarned) {
        printMsg(lvlError, format("warning: %1%") % f.str());
        haveWarned = true;
    }
}
