gw_check_realloc(void *p, size_t size, const char *filename,
                       long lineno, const char *function)
{
    struct area *area;

    if (p == NULL)
        return gw_check_malloc(size, filename, lineno, function);

    gw_assert(initialized);
    gw_assert(size > 0);

    lock();
    area = find_area(p);
    if (!area) {
        unlock();
        panic(0, "Realloc called on non-allocated area");
    }

    if (size == area->area_size) {

    } else if (size <= area->max_size) {
        change_total_size(size - area->area_size);
        area->area_size = size;
        endmark(p, size);
    } else if (size > area->max_size) {


        struct area *new_area;
        size_t new_size;
        unsigned char *new_p;

        new_size = round_pow2(size + 2 * MARKER_SIZE);
        new_p = malloc(new_size);
        new_size -= 2 * MARKER_SIZE;
        new_p += MARKER_SIZE;
        memcpy(new_p, p, area->area_size);
        fill(new_p + area->area_size, size - area->area_size,
             NEW_AREA_PATTERN);
        new_area = record_allocation(new_p, size,
                                     area->allocator.filename,
                                     area->allocator.lineno,
                                     area->allocator.function);
        new_area->max_size = new_size;
        free_area(area);

        p = new_p;
        area = new_area;
    }

    area->reallocator.filename = filename;
    area->reallocator.lineno = lineno;
    area->reallocator.function = function;
    unlock();
    return p;
}
