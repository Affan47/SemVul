GetMinRingSize( inp_ATOM* atom, QUEUE *q, AT_RANK *nAtomLevel, S_CHAR *cSource, AT_RANK nMaxRingSize )
{
    int qLen, i, j;
    AT_RANK nCurLevel, nRingSize, nMinRingSize=MAX_ATOMS+1;
    qInt at_no, next;
    int  iat_no, inext;

    while ( qLen = QueueLength( q ) ) {

        for ( i = 0; i < qLen; i ++ ) {
            if ( 0 <= QueueGet( q, &at_no ) ) {
                iat_no = (int)at_no;
                nCurLevel = nAtomLevel[iat_no] + 1;
                if ( 2*nCurLevel > nMaxRingSize + 4 ) {

                    if ( nMinRingSize < MAX_ATOMS+1 ) {
                        return (nMinRingSize >= nMaxRingSize)? 0 : nMinRingSize;
                    }
                    return 0;
                }
                for ( j = 0; j < atom[iat_no].valence; j ++ ) {
                    next  = (qInt)atom[iat_no].neighbor[j];
                    inext = (int)next;
                    if ( !nAtomLevel[inext] ) {

                        if ( 0 <= QueueAdd( q, &next ) ) {
                            nAtomLevel[inext] = nCurLevel;
                            cSource[inext] = cSource[iat_no];
                        } else {
                            return -1;
                        }
                    } else
                    if ( nAtomLevel[inext]+1 >= nCurLevel &&
                         cSource[inext] != cSource[iat_no]

                       ) {


                        if ( cSource[inext] == -1 ) {
                            return -1;
                        }
                        if ( (nRingSize = nAtomLevel[inext] + nCurLevel - 2) < nMinRingSize ) {
                            nMinRingSize = nRingSize;
                        }

                    }
                }
            } else {
                return -1;
            }
        }
    }

    if ( nMinRingSize < MAX_ATOMS+1 ) {
        return (nMinRingSize >= nMaxRingSize)? 0 : nMinRingSize;
    }

    return 0;
}
