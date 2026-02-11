ditherTo2bppLineLow(l_uint32  *lined,
                    l_int32    w,
                    l_uint32  *bufs1,
                    l_uint32  *bufs2,
                    l_int32   *tabval,
                    l_int32   *tab38,
                    l_int32   *tab14,
                    l_int32    lastlineflag)
{
l_int32  j;
l_int32  oval, tab38val, tab14val;
l_uint8  rval, bval, dval;

    if (lastlineflag == 0) {
        for (j = 0; j < w - 1; j++) {
            oval = GET_DATA_BYTE(bufs1, j);
            SET_DATA_DIBIT(lined, j, tabval[oval]);
            rval = GET_DATA_BYTE(bufs1, j + 1);
            bval = GET_DATA_BYTE(bufs2, j);
            dval = GET_DATA_BYTE(bufs2, j + 1);
            tab38val = tab38[oval];
            tab14val = tab14[oval];
            if (tab38val < 0) {
                rval = L_MAX(0, rval + tab38val);
                bval = L_MAX(0, bval + tab38val);
                dval = L_MAX(0, dval + tab14val);
            }
            else {
                rval = L_MIN(255, rval + tab38val);
                bval = L_MIN(255, bval + tab38val);
                dval = L_MIN(255, dval + tab14val);
            }
            SET_DATA_BYTE(bufs1, j + 1, rval);
            SET_DATA_BYTE(bufs2, j, bval);
            SET_DATA_BYTE(bufs2, j + 1, dval);
        }


        oval = GET_DATA_BYTE(bufs1, j);
        SET_DATA_DIBIT(lined, j, tabval[oval]);
        bval = GET_DATA_BYTE(bufs2, j);
        tab38val = tab38[oval];
        if (tab38val < 0)
            bval = L_MAX(0, bval + tab38val);
        else
            bval = L_MIN(255, bval + tab38val);
        SET_DATA_BYTE(bufs2, j, bval);
    }
    else {
        for (j = 0; j < w - 1; j++) {
            oval = GET_DATA_BYTE(bufs1, j);
            SET_DATA_DIBIT(lined, j, tabval[oval]);
            rval = GET_DATA_BYTE(bufs1, j + 1);
            tab38val = tab38[oval];
            if (tab38val < 0)
                rval = L_MAX(0, rval + tab38val);
            else
                rval = L_MIN(255, rval + tab38val);
            SET_DATA_BYTE(bufs1, j + 1, rval);
        }


        oval = GET_DATA_BYTE(bufs1, j);
        SET_DATA_DIBIT(lined, j, tabval[oval]);
    }

    return;
}
