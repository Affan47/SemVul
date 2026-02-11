opal_bitmap_get_string(opal_bitmap_t *bitmap)
{
    int i;
    char *tmp_str = NULL;
    char *bitmap_str = NULL;
    char cur_char = ' ';

    if( NULL == bitmap) {
        return NULL;
    }

    for( i = 0; i < (bitmap->array_size * SIZE_OF_CHAR); ++i) {
        if( opal_bitmap_is_set_bit(bitmap, i) ) {
            cur_char = 'X';
        } else {
            cur_char = '_';
        }

        if( NULL == bitmap_str ) {
            asprintf(&tmp_str, "%c", cur_char);
        } else {
            asprintf(&tmp_str, "%s%c", bitmap_str, cur_char);
        }

        if( NULL != bitmap_str ) {
            free(bitmap_str);
            bitmap_str = NULL;
        }
        bitmap_str = strdup(tmp_str);
        free(tmp_str);
        tmp_str = NULL;
    }

    if( NULL != tmp_str ) {
        free(tmp_str);
        tmp_str = NULL;
    }

    return bitmap_str;
}
