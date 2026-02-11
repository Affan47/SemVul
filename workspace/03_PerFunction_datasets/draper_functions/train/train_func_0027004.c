vp5_parse_vector_adjustment(VP56Context *s, VP56mv *vect)
{
    VP56RangeCoder *c = &s->c;
    VP56Model *model = s->modelp;
    int comp, di;

    for (comp=0; comp<2; comp++) {
        int delta = 0;
        if (vp56_rac_get_prob(c, model->vector_dct[comp])) {
            int sign = vp56_rac_get_prob(c, model->vector_sig[comp]);
            di  = vp56_rac_get_prob(c, model->vector_pdi[comp][0]);
            di |= vp56_rac_get_prob(c, model->vector_pdi[comp][1]) << 1;
            delta = vp56_rac_get_tree(c, vp56_pva_tree,
                                      model->vector_pdv[comp]);
            delta = di | (delta << 2);
            delta = (delta ^ -sign) + sign;
        }
        if (!comp)
            vect->x = delta;
        else
            vect->y = delta;
    }
}
