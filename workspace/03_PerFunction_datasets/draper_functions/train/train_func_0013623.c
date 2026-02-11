ya_set_full_slot_size(const int level)
{
    int word;

    word = byte2word(get_biggest_memory_bytes(level));

    if (_full_slot_size == NULL) {
        _full_slot_size = calloc(get_memory_config_level_number() + 1,
                                 sizeof(int));
        if (_full_slot_size == NULL) {
            fatal("No room\n");
        }
    }

    _full_slot_size[level] = cpow2(word / 2 + 1);
}
