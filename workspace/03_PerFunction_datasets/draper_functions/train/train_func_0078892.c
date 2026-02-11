ensRepeatconsensusCalculateMemsize(const EnsPRepeatconsensus rc)
{
    size_t size = 0;

    if (!rc)
        return 0;

    size += sizeof (EnsORepeatconsensus);

    if (rc->Name)
    {
        size += sizeof (AjOStr);

        size += ajStrGetRes(rc->Name);
    }

    if (rc->Class)
    {
        size += sizeof (AjOStr);

        size += ajStrGetRes(rc->Class);
    }

    if (rc->Type)
    {
        size += sizeof (AjOStr);

        size += ajStrGetRes(rc->Type);
    }

    if (rc->Consensus)
    {
        size += sizeof (AjOStr);

        size += ajStrGetRes(rc->Consensus);
    }

    return size;
}
