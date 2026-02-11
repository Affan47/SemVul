set_thin_widths(register pl_ptr plp)
{
    fixed dx = plp->e.p.x - plp->o.p.x, dy = plp->e.p.y - plp->o.p.y;

#define TRSIGN(v, c) ((v) >= 0 ? (c) : -(c))
    if (any_abs(dx) > any_abs(dy)) {
        plp->width.x = plp->e.cdelta.y = 0;
        plp->width.y = plp->e.cdelta.x = TRSIGN(dx, fixed_half);
    } else {
        plp->width.y = plp->e.cdelta.x = 0;
        plp->width.x = -(plp->e.cdelta.y = TRSIGN(dy, fixed_half));
    }
#undef TRSIGN
}
