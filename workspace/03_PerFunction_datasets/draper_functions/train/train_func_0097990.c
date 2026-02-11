SndTellFile(SndInfo *si)
{
    return si->writing ? -1 :
	(si->fp == stdin ? -1 : ftell(si->fp) - si->h.dataOffset);
}
