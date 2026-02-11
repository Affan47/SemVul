rms_run(rms *r, float x)
{
    if (r->rm < NEAR_ZERO) r->rm = NEAR_ZERO;

    r->rm += r->coef * (( (x * x) / r->rm) - r->rm);

    return r->rm;
}
