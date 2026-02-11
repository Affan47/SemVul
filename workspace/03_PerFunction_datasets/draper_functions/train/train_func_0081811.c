correctOverlap(void)
{

    int i;
    for (i = 0; i < nb_markers; i++)
    {
        struct box b[5];
        int max_overlap = 0, a = 0;
#if DEBUG
        fprintf(stderr, "Marker %d: %d\n", i, markers[i].dot.height);
#endif

        for (a = 0; a <= 4; a++)
        {
            align(b+a, markers+i, a);
            int total_overlap = border_overlap(b+a) + overlap(i, b+a);
#if DEBUG
            fprintf(stderr, "\tTry alignment %d: Overlap = %d %d %d\n", a, total_overlap, b[a].left, b[a].bottom);
#endif
            if (a == 0 || total_overlap < max_overlap) {
                markers[i].alignment = a;
                max_overlap = total_overlap;
            }
            if (total_overlap == 0)
                break;
        }

        markers[i].txt = b[markers[i].alignment];
    }
}
