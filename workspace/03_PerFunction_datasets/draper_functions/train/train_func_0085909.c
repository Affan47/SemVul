_AVCJapanese2ArcDBCS(AVCDBCSInfo *psDBCSInfo,
                                        const unsigned char *pszLine,
                                        int nMaxOutputLen)
{
    unsigned char *pszOut;
    int iDst;

    pszOut = psDBCSInfo->pszDBCSBuf;

    if (psDBCSInfo->nDBCSEncoding == AVC_CODE_UNKNOWN)
    {


        psDBCSInfo->nDBCSEncoding = _AVCDetectJapaneseEncoding(pszLine);


    }

    for(iDst=0; *pszLine && iDst < nMaxOutputLen; pszLine++)
    {
        if (IS_ASCII(*pszLine))
        {

            pszOut[iDst++] = *pszLine;
        }
        else if ( psDBCSInfo->nDBCSEncoding==AVC_CODE_JAP_EUC && *(pszLine+1) )
        {


            pszOut[iDst++] = *(pszLine++);
            pszOut[iDst++] = *pszLine;
        }
        else if ( IS_JAP_KANA(*pszLine) )
        {

            pszOut[iDst++] = 0x8e;
            pszOut[iDst++] = *pszLine;
        }
        else if ( *(pszLine+1) )
        {


            unsigned char leader, trailer;
            leader = *(pszLine++);
            trailer = *pszLine;

            if(leader <= 0x9F)  leader -= 0x71;
            else                leader -= 0xB1;
            leader = (leader << 1) + 1;

            if(trailer > 0x7F)  trailer --;
            if(trailer >= 0x9E)
            {
                trailer -= 0x7D;
                leader ++;
            }
            else
            {
                trailer -= 0x1F;
            }

            pszOut[iDst++] = leader | 0x80;
            pszOut[iDst++] = trailer | 0x80;
        }
        else
        {


            pszOut[iDst++] = *pszLine;
        }

    }

    pszOut[iDst] = '\0';

    return psDBCSInfo->pszDBCSBuf;
}
