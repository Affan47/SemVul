libjte_decide_file_jigdo(struct libjte_env *o,
                             char *filename, off_t size, char **mirror_name,
                             unsigned char md5[16])
{
    int ret;
    char *md5_name;

    *mirror_name = NULL;
    ret = list_file_in_jigdo(o, filename, size, &md5_name, md5);
    if (ret <= 0)
        return ret;
    *mirror_name = strdup(md5_name);
    if (*mirror_name == NULL) {
        libjte_report_no_mem(o, strlen(md5_name) + 1, 0);
        return -1;
    }
    return 1;
}
