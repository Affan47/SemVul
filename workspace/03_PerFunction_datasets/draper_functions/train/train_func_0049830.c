prompt_unref(ObPrompt *self)
{
    if (self && --self->ref == 0) {
        gint i;

        if (self->mapped)
            prompt_hide(self);

        prompt_list = g_list_remove(prompt_list, self);

        obt_keyboard_context_unref(self->ic);

        for (i = 0; i < self->n_buttons; ++i) {
            window_remove(self->button[i].window);
            XDestroyWindow(obt_display, self->button[i].window);
        }

        XDestroyWindow(obt_display, self->msg.window);
        XDestroyWindow(obt_display, self->super.window);
        g_slice_free(ObPrompt, self);
    }
}
