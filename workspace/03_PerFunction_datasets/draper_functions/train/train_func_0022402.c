ensTranslationSetStart(EnsPTranslation translation,
                              ajuint start)
{
    if (ajDebugTest("ensTranslationSetStart"))
    {
        ajDebug("ensTranslationSetStart\n"
                "  translation %p\n"
                "  start %u\n",
                translation,
                start);

        ensTranslationTrace(translation, 1);
    }

    if (!translation)
        return ajFalse;

    translation->Start = start;


    ajStrDel(&translation->Sequence);

    translation->TranscriptStart = 0;
    translation->TranscriptEnd   = 0;
    translation->SliceStart      = 0;
    translation->SliceEnd        = 0;

    return ajTrue;
}
