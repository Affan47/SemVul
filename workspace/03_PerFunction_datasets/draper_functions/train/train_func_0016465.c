parse(const char* buf, const char* venue) {
    char buf2[BLOB_SIZE];
    double dtemp;

    defaults();

    if (parse_double(buf, "<mod_time>", mod_time)) {

        if (mod_time > dtime()) mod_time = dtime();
    }
    extract_venue(buf, venue, buf2, sizeof(buf2));
    parse_double(buf2, "<disk_max_used_gb>", disk_max_used_gb);
    parse_double(buf2, "<disk_max_used_pct>", disk_max_used_pct);
    parse_double(buf2, "<disk_min_free_gb>", disk_min_free_gb);
    parse_double(buf2, "<work_buf_min_days>", work_buf_min_days);
    if (parse_double(buf2, "<ram_max_used_busy_pct>", dtemp)) {
        ram_max_used_busy_frac = dtemp/100.;
    }
    if (parse_double(buf2, "<ram_max_used_idle_pct>", dtemp)) {
        ram_max_used_idle_frac = dtemp/100.;
    }
    parse_double(buf2, "<max_ncpus_pct>", max_ncpus_pct);
}
