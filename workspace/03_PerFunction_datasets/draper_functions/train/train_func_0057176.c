worker_on_session_exited (GdmDBusWorker          *worker,
                          const char             *service_name,
                          int                     status,
                          GdmSessionConversation *conversation)
{
        GdmSession *self = conversation->session;

        self->priv->session_conversation = NULL;

        if (WIFEXITED (status)) {
                g_debug ("GdmSession: Emitting 'session-exited' signal with exit code '%d'",
                  WEXITSTATUS (status));
                g_signal_emit (self, signals[SESSION_EXITED], 0, WEXITSTATUS (status));
        } else if (WIFSIGNALED (status)) {
                g_debug ("GdmSession: Emitting 'session-died' signal with signal number '%d'",
                  WTERMSIG (status));
                g_signal_emit (self, signals[SESSION_DIED], 0, WTERMSIG (status));
        }
}
