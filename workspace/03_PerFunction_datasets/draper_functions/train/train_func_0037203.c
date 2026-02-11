CORD_next(CORD_pos p)
{
    if (p[0].cur_pos < p[0].cur_end - 1) {
        p[0].cur_pos++;
    } else {
        CORD__next(p);
    }
}
