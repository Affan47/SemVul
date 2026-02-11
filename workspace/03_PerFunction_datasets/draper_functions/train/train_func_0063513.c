is_path_component_character(wchar_t c)
{

    return tok_is_string_character(c, true) && ! wcschr(L"/={,}'\"", c);
}
