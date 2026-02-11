archive_compressor_gzip_options(struct archive_write *a, const char *key,
    const char *value)
{
    struct private_config *config;

    config = (struct private_config *)a->compressor.config;
    if (strcmp(key, "compression-level") == 0) {
        if (value == NULL || !(value[0] >= '0' && value[0] <= '9') ||
            value[1] != '\0')
            return (ARCHIVE_WARN);
        config->compression_level = value[0] - '0';
        return (ARCHIVE_OK);
    }

    return (ARCHIVE_WARN);
}
