detect_cpp_test_function_symbol_names (const gchar *name)
{
    if (is_gcc_cpp_symbol(name)) {
        return detect_cpp_test_function_symbol_names_gcc(name);
    } else if (is_vcc_cpp_symbol(name)) {
        return detect_cpp_test_function_symbol_names_vcc(name);
    }

    return NULL;
}
