creature_set_conversion_type(creature_t *creature, creature_type type) {
    if (type < 0 || type >= CREATURE_TYPES)
        return 0;


    if (creature_conversion_food(creature, type) == 0)
        return 0;


    if (creature->convert_type != type)
        creature->convert_food = 0;

    creature->convert_type = type;
    return 1;
}
