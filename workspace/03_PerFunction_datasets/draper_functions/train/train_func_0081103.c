client_get_state(ObClient *self)
{
    guint32 *state;
    guint num;

    if (OBT_PROP_GETA32(self->window, NET_WM_STATE, ATOM, &state, &num)) {
        gulong i;
        for (i = 0; i < num; ++i) {
            if (state[i] == OBT_PROP_ATOM(NET_WM_STATE_MODAL))
                self->modal = TRUE;
            else if (state[i] == OBT_PROP_ATOM(NET_WM_STATE_SHADED))
                self->shaded = TRUE;
            else if (state[i] == OBT_PROP_ATOM(NET_WM_STATE_HIDDEN))
                self->iconic = TRUE;
            else if (state[i] == OBT_PROP_ATOM(NET_WM_STATE_SKIP_TASKBAR))
                self->skip_taskbar = TRUE;
            else if (state[i] == OBT_PROP_ATOM(NET_WM_STATE_SKIP_PAGER))
                self->skip_pager = TRUE;
            else if (state[i] == OBT_PROP_ATOM(NET_WM_STATE_FULLSCREEN))
                self->fullscreen = TRUE;
            else if (state[i] == OBT_PROP_ATOM(NET_WM_STATE_MAXIMIZED_VERT))
                self->max_vert = TRUE;
            else if (state[i] == OBT_PROP_ATOM(NET_WM_STATE_MAXIMIZED_HORZ))
                self->max_horz = TRUE;
            else if (state[i] == OBT_PROP_ATOM(NET_WM_STATE_ABOVE))
                self->above = TRUE;
            else if (state[i] == OBT_PROP_ATOM(NET_WM_STATE_BELOW))
                self->below = TRUE;
            else if (state[i] == OBT_PROP_ATOM(NET_WM_STATE_DEMANDS_ATTENTION))
                self->demands_attention = TRUE;
            else if (state[i] == OBT_PROP_ATOM(OB_WM_STATE_UNDECORATED))
                self->undecorated = TRUE;
        }

        g_free(state);
    }
}
