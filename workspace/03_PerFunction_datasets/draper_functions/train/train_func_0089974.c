collect_session_info (uid_t uid,
                      pid_t pid)
{
        SessionInfo *si;
        gboolean     ret;

        si = g_new0 (SessionInfo, 1);

        si->uid = uid;
        si->pid = pid;

        ret = fill_session_info (si);
        if (ret) {
                print_session_info (si);
        }

        session_info_free (si);

        return ret;
}
