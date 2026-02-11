client_prompt_kill(ObClient *self)
{

    if (!self->kill_prompt) {
        ObPromptAnswer answers[] = {
            { 0, OB_KILL_RESULT_NO },
            { 0, OB_KILL_RESULT_YES }
        };
        gchar *m;
        const gchar *y, *title;

        title = self->original_title;
        if (title[0] == '\0') {

            ObClient *p = client_search_top_direct_parent(self);
            if (p) title = p->original_title;
        }

        if (client_on_localhost(self)) {
            const gchar *sig;

            if (self->kill_level == 0)
                sig = "terminate";
            else
                sig = "kill";

            m = g_strdup_printf
                (_("The window \"%s\" does not seem to be responding.  Do you want to force it to exit by sending the %s signal?"),
                 title, sig);
            y = _("End Process");
        }
        else {
            m = g_strdup_printf
                (_("The window \"%s\" does not seem to be responding.  Do you want to disconnect it from the X server?"),
                 title);
            y = _("Disconnect");
        }

        answers[0].text = _("Cancel");
        answers[1].text = y;

        self->kill_prompt = prompt_new(m, NULL, answers,
                                       sizeof(answers)/sizeof(answers[0]),
                                       OB_KILL_RESULT_NO,
                                       OB_KILL_RESULT_NO,
                                       client_kill_requested,
                                       client_kill_cleanup,
                                       self);
        g_free(m);
    }

    prompt_show(self->kill_prompt, self, TRUE);
}
