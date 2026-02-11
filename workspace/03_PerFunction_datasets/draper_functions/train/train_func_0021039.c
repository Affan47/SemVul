spif_array_map_new(void)
{
    spif_array_t self;

    self = SPIF_ALLOC(array);
    if (!spif_array_map_init(self)) {
        SPIF_DEALLOC(self);
        self = SPIF_NULL_TYPE(array);
    }
    return self;
}
