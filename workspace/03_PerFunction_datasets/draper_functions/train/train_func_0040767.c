update_admpwd(char *admroot, char *newuid, char *newpw)
{
    FILE *f;
    int cnt;
    char filename[BIG_LINE];
    char outbuf[BIG_LINE];

    apr_snprintf(filename, sizeof(filename), "%s/admpw", admroot);

    f = fopen(filename, "w");
    if (f==NULL) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, 0, NULL,
                     "Can not open admpw file [%s] for writing", filename);
        return 0;
    }

    apr_snprintf(outbuf, sizeof(outbuf), "%s:%s", newuid, newpw);

    cnt = fprintf(f,"%s", outbuf);

    if (cnt != (int)strlen(outbuf)) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, 0, NULL,
                     "Failed to write to admpw file [%s]", filename);
        fclose(f);
        return 0;
    }

    fclose(f);
    return 1;
}
