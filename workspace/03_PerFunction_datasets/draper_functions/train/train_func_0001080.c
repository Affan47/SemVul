accumulator_output(struct fortuna_state *st, unsigned char *dst, size_t len)
{


    if (st->pool0_bytes >= MIN_POOL_LEN && enough_time_passed(st))
        accumulator_reseed(st);

    generator_output(st, dst, len);
}
