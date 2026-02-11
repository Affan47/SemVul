get_fapi_glyph_data(FT_Incremental a_info, FT_UInt a_index, FT_Data * a_data)
{
    gs_fapi_font *ff = a_info->fapi_font;
    int length = 0;
    ff_face *face = (ff_face *) ff->server_font_data;


    ff->need_decrypt = true;


    if (a_info->glyph_data_in_use) {
        unsigned char *buffer = NULL;

        length = ff->get_glyph(ff, a_index, NULL, 0);
        if (length == 65535)
            return FT_Err_Invalid_Glyph_Index;

        buffer = gs_malloc((gs_memory_t *) a_info->fapi_font->memory, length, 1, "get_fapi_glyph_data");
        if (!buffer)
            return FT_Err_Out_Of_Memory;

        length = ff->get_glyph(ff, a_index, buffer, length);
        if (length == 65535) {
            gs_free((gs_memory_t *) a_info->fapi_font->memory, buffer, 0, 0,
                    "get_fapi_glyph_data");
            return FT_Err_Invalid_Glyph_Index;
        }
        a_data->pointer = buffer;
    }
    else {


        const void *saved_char_data = ff->char_data;


        length =
            ff->get_glyph(ff, a_index, a_info->glyph_data,
                          (ushort) a_info->glyph_data_length);
        if (length == -1) {
            ff->char_data = saved_char_data;
            return FT_Err_Unknown_File_Format;
        }


        if (length > a_info->glyph_data_length) {
            if (a_info->glyph_data) {
                gs_free((gs_memory_t *) a_info->fapi_font->memory,
                        a_info->glyph_data, 0, 0, "get_fapi_glyph_data");
            }

            a_info->glyph_data =
                gs_malloc((gs_memory_t *) a_info->fapi_font->memory, length,
                          1, "get_fapi_glyph_data");

            if (!a_info->glyph_data) {
                a_info->glyph_data_length = 0;
                return FT_Err_Out_Of_Memory;
            }
            a_info->glyph_data_length = length;
            ff->char_data = saved_char_data;
            length = ff->get_glyph(ff, a_index, a_info->glyph_data, length);
            if (length == -1)
                return FT_Err_Unknown_File_Format;
        }


        a_data->pointer = a_info->glyph_data;

        a_info->glyph_data_in_use = true;
    }

    a_data->length = length;
    return 0;
}
