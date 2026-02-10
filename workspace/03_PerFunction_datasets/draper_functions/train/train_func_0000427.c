G_quant_set_pos_infinite_rule(struct Quant *q, DCELL dRight, CELL c)
{
    q->infiniteDRight = dRight;
    q->infiniteCRight = c;
    quant_update_limits(q, dRight, dRight, c, c);


    if (q->fp_lookup.active) {
	q->fp_lookup.inf_dmax = q->infiniteDRight;
	q->fp_lookup.inf_max = q->infiniteCRight;
    }
    q->infiniteRightSet = 1;
}
