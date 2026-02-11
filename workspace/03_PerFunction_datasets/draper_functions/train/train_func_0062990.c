pdfmark_scan_rect(gs_rect * prect, const gs_param_string * str,
                  const gs_matrix * pctm)
{
    uint size = str->size;
    double v[4];
#define MAX_RECT_STRING 100
    char chars[MAX_RECT_STRING + 3];
    int end_check;

    if (str->size > MAX_RECT_STRING)
        return_error(gs_error_limitcheck);
    memcpy(chars, str->data, size);
    strcpy(chars + size, " 0");
    if (sscanf(chars, "[%lg %lg %lg %lg]%d",
               &v[0], &v[1], &v[2], &v[3], &end_check) != 5
        )
        return_error(gs_error_rangecheck);
    gs_point_transform(v[0], v[1], pctm, &prect->p);
    gs_point_transform(v[2], v[3], pctm, &prect->q);
    return 0;
}
