duo_check_groups(struct passwd *pw, char **groups, int groups_cnt)
{
    int i;

    if (groups_cnt > 0) {
        int matched = 0;

        if (ga_init(pw->pw_name, pw->pw_gid) < 0) {
            duo_log(LOG_ERR, "Couldn't get groups",
                pw->pw_name, NULL, strerror(errno));
            return (-1);
        }
        for (i = 0; i < groups_cnt; i++) {
            if (ga_match_pattern_list(groups[i])) {
                matched = 1;
                break;
            }
        }
        ga_free();


        return matched;
    } else {
        return 1;
    }
}
