file_name_is_full_path(Dwarf_Small  *fname)
{
    Dwarf_Small firstc = *fname;
    if(is_path_separator(firstc)) {

        return 1;
    }
    if(!firstc) {
        return 0;
    }
#ifdef HAVE_WINDOWS_PATH
    if((firstc >= 'A' && firstc <= 'Z') ||
        (firstc >= 'a' && firstc <= 'z')) {

        Dwarf_Small secondc = fname[1];
        if (secondc == ':') {
            return 1;
        }
    }
#endif
    return 0;
}
