glusterd_query_extutil (char *resbuf, runner_t *runner)
{
        char               *ptr = NULL;
        int                 ret = 0;

        runner_redir (runner, STDOUT_FILENO, RUN_PIPE);
        if (runner_start (runner) != 0) {
                gf_log ("", GF_LOG_ERROR, "spawning child failed");

                return -1;
        }

        ptr = fgets(resbuf, PATH_MAX, runner_chio (runner, STDOUT_FILENO));
        if (ptr)
                resbuf[strlen(resbuf)-1] = '\0';

        ret = runner_end (runner);
        if (ret)
                gf_log ("", GF_LOG_ERROR, "reading data from child failed");

        return ret ? -1 : 0;
}
