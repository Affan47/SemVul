order_font_data(gs_copied_font_data_t *cfdata, gs_memory_t *memory)
{
    int i, j = 0;

    gs_copied_glyph_name_t **a = (gs_copied_glyph_name_t **)gs_alloc_byte_array(memory, cfdata->num_glyphs,
        sizeof(gs_copied_glyph_name_t *), "order_font_data");
    if (a == NULL)
        return_error(gs_error_VMerror);
    j = 0;
    for (i = 0; i < cfdata->glyphs_size; i++) {
        if (cfdata->glyphs[i].used) {
            if (j >= cfdata->num_glyphs)
                return_error(gs_error_unregistered);
            a[j++] = &cfdata->names[i];
        }
    }
    qsort(a, cfdata->num_glyphs, sizeof(*a), compare_glyph_names);
    for (j--; j >= 0; j--)
        cfdata->glyphs[j].order_index = a[j] - cfdata->names;
    gs_free_object(memory, a, "order_font_data");
    return 0;
}
