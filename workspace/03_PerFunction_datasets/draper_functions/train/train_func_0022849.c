dfb_clip_triangle_precheck( const DFBRegion *clip, const DFBTriangle *tri )
{
    int x, y, w, h;

    x = MIN (MIN (tri->x1, tri->x2), tri->x3);
    y = MIN (MIN (tri->y1, tri->y2), tri->y3);
    w = MAX (MAX (tri->x1, tri->x2), tri->x3) - x;
    h = MAX (MAX (tri->y1, tri->y2), tri->y3) - y;

    if (clip->x1 > x ||
        clip->x2 < x + w ||
        clip->y1 > y ||
        clip->y2 < y + h)
      return DFB_FALSE;

    return DFB_TRUE;
}
