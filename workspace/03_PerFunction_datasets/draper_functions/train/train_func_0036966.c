interpretSuffix(char c)
{
    const ant_sensor_type_t *st=ant_sensor_types;

    do {
        if (st->suffix==c) return st->type;
    } while (++st, st->type != ANTChannel::CHANNEL_TYPE_GUARD);

    return -1;
}
