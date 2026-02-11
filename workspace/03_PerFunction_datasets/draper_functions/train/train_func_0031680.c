ajRangeSeqStuffPep(const AjPRange thys, AjPSeq seq, ajint frame)
{
    ajuint nr;
    ajuint i;
    ajuint j;
    ajuint lasten = 0;
    ajuint lastst = 0;
    ajuint len;
    ajuint st;
    ajuint en;
    ajuint nbases = 0;
    ajuint shift = 0;
    AjBool result = ajFalse;
    AjPStr outstr = NULL;
    ajint lastframe = 0;

    nr = thys->n;

    if(!nr)
        return ajFalse;

    if(frame > 0)
    {
        for(i = 0; i < nr; i++)
        {
            result = ajTrue;

            if(!ajRangeElementGetValues(thys, i, &st, &en))
                continue;

            shift = nbases%3;
            nbases += en - st + 1;

            if((frame) % 3 != (((ajint) st - (ajint) shift) % 3))
                continue;


            --st;
            --en;
            len = en - st;

            ajDebug("lasten:%u st:%u shift:%u frame:%d lastframe:%d\n",
                    lasten, st, shift, frame, lastframe);
            for(j = lasten; j < st; j++)
                ajStrAppendC(&outstr, " ");

            if(shift && (frame != lastframe))
                for(j = 3; j > shift; j--)
                    ajStrAppendC(&outstr, " ");

            ajStrAppendSubS(&outstr, ajSeqGetSeqS(seq), lastst, lastst + len);
            lastst = lastst + len + 1;
            lasten = en + 1;
            lastframe = frame;
        }

        ajSeqAssignSeqS(seq, outstr);
        ajStrDel(&outstr);
    }
    else if (frame < 0)
    {
        ajSeqReverseOnly(seq);

        for(i = nr; i > 0; i--)
        {
            result = ajTrue;
            if(!ajRangeElementGetValues(thys, i - 1, &st, &en))
                continue;

            if((-frame) % 3 != (((ajint) st) % 3))
                continue;


            --st;
            --en;
            len = en - st;

            for(j = lasten; j < st; j++)
                ajStrAppendC(&outstr, " ");

            ajStrAppendSubS(&outstr, ajSeqGetSeqS(seq), lastst, lastst + len);
            lastst = lastst + len + 1;
            lasten = en + 1;
        }

        ajSeqAssignSeqS(seq, outstr);
        ajStrDel(&outstr);
    }


    return result;
}
