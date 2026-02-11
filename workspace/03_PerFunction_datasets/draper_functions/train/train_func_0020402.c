ensQcsequenceCalculateMemsize(const EnsPQcsequence qcs)
{
    size_t size = 0;

    if (!qcs)
        return 0;

    size += sizeof (EnsOQcsequence);

    size += ensQcdatabaseCalculateMemsize(qcs->Qcdatabase);

    if (qcs->Name)
    {
        size += sizeof (AjOStr);

        size += ajStrGetRes(qcs->Name);
    }

    if (qcs->Accession)
    {
        size += sizeof (AjOStr);

        size += ajStrGetRes(qcs->Accession);
    }

    if (qcs->Type)
    {
        size += sizeof (AjOStr);

        size += ajStrGetRes(qcs->Type);
    }

    if (qcs->Description)
    {
        size += sizeof (AjOStr);

        size += ajStrGetRes(qcs->Description);
    }

    return size;
}
