SLRandomLevel(void)
{
    int level = 1;
    SL_RANDOM_DECL;

    SL_RANDOM_INIT(SL_RANDOM_SEED);

    while ((SL_RANDOM & 0x01) && level < SL_MAX_LEVEL) ++level;
    return level;
}
