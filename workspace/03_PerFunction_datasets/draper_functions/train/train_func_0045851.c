file_existsp(const char *filepath)
{
    FILE *f;

    SCM_ASSERT(filepath);

    if (!ABSOLUTE_PATHP(filepath))
        return scm_false;

    f = fopen(filepath, "r");
    if (f) {
        fclose(f);
        return scm_true;
    } else {
        return scm_false;
    }
}
