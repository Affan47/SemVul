ensSliceFetchSliceexpanded(EnsPSlice slice,
                                  ajint five,
                                  ajint three,
                                  AjBool force,
                                  ajint *Pfshift,
                                  ajint *Ptshift,
                                  EnsPSlice *Pslice)
{
    ajint sshift = 0;
    ajint eshift = 0;

    ajint srstart = 0;
    ajint srend   = 0;

    AjBool circular = AJFALSE;

    if (ajDebugTest("ensSliceFetchSliceexpanded"))
        ajDebug("ensSliceFetchSliceexpanded\n"
                "  slice %p\n"
                "  five %d\n"
                "  three %d\n"
                "  force '%B'\n"
                "  Pfshift %p\n"
                "  Ptshift %p\n"
                "  Pslice %p\n",
                slice,
                five,
                three,
                force,
                Pfshift,
                Ptshift,
                Pslice);

    if (!slice)
        return ajFalse;

    if (!Pfshift)
        return ajFalse;

    if (!Ptshift)
        return ajFalse;

    if (!Pslice)
        return ajFalse;

    *Pslice = NULL;

    if (slice->Sequence)
    {
        ajDebug("ensSliceFetchSliceexpanded cannot expand an Ensembl Slice "
                "with an attached sequence.\n");

        return ajFalse;
    }

    if (slice->Strand > 0)
    {
        sshift = five;
        eshift = three;
    }
    else
    {
        sshift = three;
        eshift = five;
    }

    srstart = slice->Start - sshift;
    srend   = slice->End   + eshift;

    ensSliceIsCircular(slice, &circular);

    if (
        (
            (srstart <= 0)
            ||
            (srstart > ensSliceGetSeqregionLength(slice))
            ||
            (srend <= 0)
            ||
            (srend > ensSliceGetSeqregionLength(slice))
         )
        &&
        (circular == ajTrue)
        )
    {
        if (srstart <= 0)
            srstart += ensSliceGetSeqregionLength(slice);

        if (srstart > ensSliceGetSeqregionLength(slice))
            srstart -= ensSliceGetSeqregionLength(slice);

        if (srend <= 0)
            srend += ensSliceGetSeqregionLength(slice);

        if (srend > ensSliceGetSeqregionLength(slice))
            srend -= ensSliceGetSeqregionLength(slice);
    }

    if ((srstart > srend)  && (circular == ajFalse))
    {
        if (force)
        {


            if (sshift < 0)
            {


                srstart = srend - 1;

                sshift = slice->Start - srstart;
            }
            else
            {


                if (eshift < 0)
                {
                    srend = srstart + 1;

                    eshift = srend - slice->End;
                }

                *Pfshift = (slice->Strand >= 0) ? eshift : sshift;
                *Ptshift = (slice->Strand >= 0) ? sshift : eshift;
            }
        }

        if (srstart > srend)
        {


            ajDebug("ensSliceFetchSliceexpanded requires the Slice "
                    "start %d to be less than the Slice end %d "
                    "coordinate.\n",
                    srstart, srend);

            return ajFalse;
        }
    }

    if (slice->Adaptor)
        ensSliceadaptorFetchBySeqregionIdentifier(
            slice->Adaptor,
            ensSeqregionGetIdentifier(slice->Seqregion),
            srstart,
            srend,
            slice->Strand,
            Pslice);
    else
        *Pslice = ensSliceNewIni(slice->Adaptor,
                                 slice->Seqregion,
                                 srstart,
                                 srend,
                                 slice->Strand);

    return ajTrue;
}
