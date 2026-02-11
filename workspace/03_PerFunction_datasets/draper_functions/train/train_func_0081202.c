cmp_galms_gain(const void *e1, const void *e2)
{
    const Galms *g1 = e1;
    const Galms *g2 = e2;

    if (g1->gain > g2->gain) {
        return 1;
    } else if (g1->gain < g2->gain) {
        return -1;
    } else {
        if (g1->size < g2->size) {
            return 1;
        } else {
            return -1;
        }
    }
}
