gfork_l_sigchld(
    void *                              user_arg)
{
    int                                 child_pid;
    int                                 child_status;
    int                                 child_rc;
    globus_bool_t                       dead;

    gfork_log(2, "Sigint child\n");
    globus_mutex_lock(&gfork_l_mutex);
    {
        while((child_pid = waitpid(-1, &child_status, WNOHANG)) > 0)
        {
            dead = GLOBUS_FALSE;
            if(WIFEXITED(child_status))
            {

                child_rc = WEXITSTATUS(child_status);
                dead = GLOBUS_TRUE;
            }
            else if(WIFSIGNALED(child_status))
            {

                dead = GLOBUS_TRUE;
            }

            if(dead)
            {
                gfork_l_connection_count--;
                gfork_l_dead_kid(child_pid);

                gfork_log(2, "Child %d completed\n", child_pid);
            }
        }
    }
    globus_mutex_unlock(&gfork_l_mutex);
}
