image_list_is_file_supported( const char* name )
{
    const char* ext = strrchr( name, '.' );
    if( ! ext )
        return FALSE;
    ++ext;

    return !!g_slist_find_custom ( supported_formats, ext,  (GCompareFunc)g_ascii_strcasecmp);
}
