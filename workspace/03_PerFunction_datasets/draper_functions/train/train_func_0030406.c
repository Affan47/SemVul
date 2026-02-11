ensTranscriptSetCanonical(EnsPTranscript transcript,
                                 AjBool canonical)
{
    AjBool *Pcanonical = NULL;

    if (!transcript)
        return ajFalse;

    if (!transcript->Canonical)
    {
        AJNEW0(Pcanonical);

        transcript->Canonical = Pcanonical;
    }

    *transcript->Canonical = canonical;

    return ajTrue;
}
