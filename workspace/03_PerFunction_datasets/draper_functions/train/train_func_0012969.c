set_length(size_t len) {
    if (number_found && x_string_len<len) freeset(number_found, 0);
    x_string_len = len;
    initialized  = false;
}
