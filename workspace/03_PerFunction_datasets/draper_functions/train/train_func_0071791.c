get_part_stats(const char *key, const char *val, void *rock)
{
    int meta = *((int*) rock);
    const char *part, *path;
    struct statvfs s;
    long blocks_used;
    long blocks_percent_used;

    if (meta) {
        if (strncmp("meta", key, 4)) return;
	key += 4;
    }
    if (strncmp("partition-", key, 10)) return;

    part = key+10;
    path = val;

    if (statvfs(path, &s)) return;

    blocks_used = s.f_blocks - s.f_bfree;
    blocks_percent_used = (long)
	(blocks_used * 100.0 / (blocks_used + s.f_bavail) + 0.5);

    printf("%-12s %12ld %12ld %12ld %3ld%% %s\n",
	   part,
	   (long) (s.f_blocks * (s.f_frsize / 1024.0)),
	   (long) ((s.f_blocks - s.f_bfree) * (s.f_frsize / 1024.0)),
	   (long) (s.f_bavail * (s.f_frsize / 1024.0)),
	   blocks_percent_used, path);
}
