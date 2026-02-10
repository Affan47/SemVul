allocate_array (matches_and_old_values_array *array, unsigned long max_bytes)
{

    unsigned long bytes_to_allocate = sizeof(matches_and_old_values_array) + sizeof(matches_and_old_values_swath);

    if (!(array = realloc(array, bytes_to_allocate))) return NULL;

    array->bytes_allocated = bytes_to_allocate;
    array->max_needed_bytes = max_bytes;

    return array;
}
