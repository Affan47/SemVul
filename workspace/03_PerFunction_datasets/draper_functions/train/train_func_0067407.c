generate_result_mask(ALI_TSTACK < unsigned char >*stack)
{
    ALI_SEQUENCE   *seq;
    float           cost_of_bindings;
    ALI_MAP        *map;
    unsigned long   seq_pos, dest_pos;
    long            i;

    map = new ALI_MAP(start_x, end_x, start_y, end_y);

    seq_pos = start_x;
    dest_pos = 0;
    for (i = (long) stack->akt_size() - 1; i >= 0; i--) {
        switch (stack->get(i)) {
            case ALI_PREALIGNER_INS:
                map->set(seq_pos++, dest_pos, 1);
                break;
            case ALI_PREALIGNER_SUB:
                map->set(seq_pos++, dest_pos++, 0);
                break;
            case ALI_PREALIGNER_DEL:
                dest_pos++;
                break;
            case ALI_PREALIGNER_INS | ALI_PREALIGNER_MULTI_FLAG:
                map->set(seq_pos, dest_pos, 1);
                map->undefine(seq_pos++);
                break;
            case ALI_PREALIGNER_SUB | ALI_PREALIGNER_MULTI_FLAG:
                map->set(seq_pos, dest_pos++, 0);
                map->undefine(seq_pos++);
                break;
            case ALI_PREALIGNER_DEL | ALI_PREALIGNER_MULTI_FLAG:
                dest_pos++;
                break;
            default:
                ali_fatal_error("Unexpected value",
                                "ALI_PREALIGNER::generate_result_mask()");
        }
    }

    if (result_mask_counter > 0)
        result_mask_counter--;

    seq = map->sequence_without_inserts(profile->sequence());
    cost_of_bindings = profile->w_binding(map->first_reference_base(), seq);
    delete          seq;


    result_mask.insert(map, cost_of_bindings);
}
