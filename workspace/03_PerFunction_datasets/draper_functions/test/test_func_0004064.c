fmtcmp(const char *fmt1, const char *fmt2)
{
    if (fmt1 == NULL) {
        return fmt2 == NULL || strcmp(fmt2, "B") == 0;
    }
    if (fmt2 == NULL) {
        return fmt1 == NULL || strcmp(fmt1, "B") == 0;
    }
    return strcmp(fmt1, fmt2) == 0;
}
