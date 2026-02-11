tensor_patch_bbox(gs_fixed_rect *r, const tensor_patch *p)
{
    int i, j;

    r->p.x = r->q.x = p->pole[0][0].x;
    r->p.y = r->q.y = p->pole[0][0].y;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            const gs_fixed_point *q = &p->pole[i][j];

            if (r->p.x > q->x)
                r->p.x = q->x;
            if (r->p.y > q->y)
                r->p.y = q->y;
            if (r->q.x < q->x)
                r->q.x = q->x;
            if (r->q.y < q->y)
                r->q.y = q->y;
        }
    }
}
