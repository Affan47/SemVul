HandleBracket(char Char)
{
    unsigned long BrOffset;
    struct ErrInfo *ei;
    char TmpC, Match;
    char ABuf[2], BBuf[2];
    char *TmpPtr;

    AddBracket(Char);

    if ((BrOffset = BrackIndex(Char)) != ~0UL)
    {
        if (BrOffset & 1)
        {
            if ((ei = PopErr(&CharStack)))
            {
                Match = MatchBracket(*(ei->Data));

                if (ei->Flags & efNoItal)
                {
                    if (ItState == itOn)
                    {
                        TmpPtr = BufPtr;
                        SKIP_AHEAD(TmpPtr, TmpC, TmpC == '}');


                        if ( !strchr(LTX_SmallPunc, *TmpPtr) &&
                             !strchr(LTX_SmallPunc, *(TmpPtr-2)) )
                            HERE(1, emNoItFound);
                    }

                    ItState = FALSE;
                }
                else if (ei->Flags & efItal)
                    ItState = TRUE;


                if (ei->Flags & efMath)
                {
                    MathMode = 1;
                }
                else if (ei->Flags & efNoMath)
                {
                    MathMode = 0;
                }

                FreeErrInfo(ei);
            }
            else
                Match = 0;

            if (Match != Char)
            {
                ABuf[0] = Match;
                BBuf[0] = Char;
                ABuf[1] = BBuf[1] = 0;
                if (Match)
                    PrintError(CurStkName(&InputStack), RealBuf,
                               BufPtr - Buf - 1, 1, Line, emExpectC,
                               ABuf, BBuf);
                else
                    HEREA(1, emSoloC, BBuf);
            }

        }
        else
        {
            if ((ei = PushChar(Char, Line, BufPtr - Buf - 1,
                               &CharStack, MakeCpy())))
            {
                if (Char == '{')
                {
                    switch (ItFlag)
                    {
                    default:
                        ei->Flags |= ItFlag;
                        ItFlag = efNone;
                        break;
                    case efNone:
                        ei->Flags |= ItState ? efItal : efNoItal;
                    }

                    switch (MathFlag)
                    {
                    default:
                        ei->Flags |= MathFlag;
                        MathFlag = efNone;
                        break;
                    case efNone:
                        ei->Flags |= MathMode ? efMath : efNoMath;
                    }
                }
            }

            else
                PrintPrgErr(pmNoStackMem);
        }
    }
}
