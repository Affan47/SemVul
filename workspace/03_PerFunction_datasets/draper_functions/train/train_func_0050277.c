pretty_print_dashed_line(int len) {
    static const char dashes[9] = "--------";

    while (len >= 8) {
        printf("%8.8s", dashes);
        len -= 8;
    }
    printf("%*.*s\n", len, len, dashes);
}
