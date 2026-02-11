dumpstrings()
{
    struct string *stringp;

    dseg();
    for (stringp = laststring; stringp != NULL; stringp = stringp->snext)
    {
	outnlabel(stringp->slabel);
	defstr(stringp->sptr, stringp->stop, TRUE);
	dataoffset += stringp->stop - stringp->sptr + 1;
    }
}
