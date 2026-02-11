AddX(Array aposnew, int *count_p, Array aconnew, int *count_conn,
     float x, float y, float epsilonx, float epsilony,
     int regcolors, RGBColor color, Array acolorsnew) {

    Point newpoint;
    Line  newcon;
    int tmp_p, tmp_c;

    tmp_p = *count_p;
    tmp_c = *count_conn;
    newpoint = DXPt(x-epsilonx, y-epsilony, 0.0);
    if (!DXAddArrayData(aposnew, tmp_p, 1, (Pointer)&newpoint))
        goto error;
    if (!regcolors)
        if (!DXAddArrayData(acolorsnew, tmp_p, 1, (Pointer)&color))
            goto error;
    tmp_p++;
    newpoint = DXPt(x+epsilonx, y+epsilony, 0.0);
    if (!DXAddArrayData(aposnew, tmp_p, 1, (Pointer)&newpoint))
        goto error;
    if (!regcolors)
        if (!DXAddArrayData(acolorsnew, tmp_p, 1, (Pointer)&color))
            goto error;
    tmp_p++;
    newpoint = DXPt(x+epsilonx, y-epsilony, 0.0);
    if (!DXAddArrayData(aposnew, tmp_p, 1, (Pointer)&newpoint))
        goto error;
    if (!regcolors)
        if (!DXAddArrayData(acolorsnew, tmp_p, 1, (Pointer)&color))
            goto error;
    tmp_p++;
    newpoint = DXPt(x-epsilonx, y+epsilony, 0.0);
    if (!DXAddArrayData(aposnew, tmp_p, 1, (Pointer)&newpoint))
        goto error;
    if (!regcolors)
        if (!DXAddArrayData(acolorsnew, tmp_p, 1, (Pointer)&color))
            goto error;
    tmp_p++;
    newcon = DXLn(tmp_p-4, tmp_p-3);
    if (!(DXAddArrayData(aconnew, tmp_c, 1, (Pointer)&newcon)))
        goto error;
    tmp_c++;
    newcon = DXLn(tmp_p-2, tmp_p-1);
    if (!(DXAddArrayData(aconnew, tmp_c, 1, (Pointer)&newcon)))
        goto error;
    tmp_c++;

    *count_p = tmp_p;
    *count_conn = tmp_c;
    return OK;

error:
    return ERROR;
}
