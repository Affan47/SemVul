load_sparse_files(const char *fname, int max_size)
{
    int fd;
    struct sparse_file *s;
    int files;
    struct sparse_file **out_s;

    fd = open(fname, O_RDONLY | O_BINARY);
    if (fd < 0) {
        die("cannot open '%s'\n", fname);
    }

    s = sparse_file_import_auto(fd, false);
    if (!s) {
        die("cannot sparse read file '%s'\n", fname);
    }

    files = sparse_file_resparse(s, max_size, NULL, 0);
    if (files < 0) {
        die("Failed to resparse '%s'\n", fname);
    }

    out_s = calloc(sizeof(struct sparse_file *), files + 1);
    if (!out_s) {
        die("Failed to allocate sparse file array\n");
    }

    files = sparse_file_resparse(s, max_size, out_s, files);
    if (files < 0) {
        die("Failed to resparse '%s'\n", fname);
    }

    return out_s;
}
