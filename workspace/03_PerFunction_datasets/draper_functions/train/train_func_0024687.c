on_glade_drop_possible (IAnjutaEditor* editor,
                        IAnjutaIterable* iterator,
                        CppJavaPlugin* lang_plugin)
{
    switch (lang_plugin->filetype)
    {
        case LS_FILE_C:
        case LS_FILE_CHDR:
            return TRUE;
        default:
            return FALSE;
    }
}
