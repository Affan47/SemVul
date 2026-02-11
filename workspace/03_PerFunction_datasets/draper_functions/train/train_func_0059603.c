client_change_allowed_actions(ObClient *self)
{
    gulong actions[12];
    gint num = 0;


    if (self->type != OB_CLIENT_TYPE_DESKTOP)
        actions[num++] = OBT_PROP_ATOM(NET_WM_ACTION_CHANGE_DESKTOP);

    if (self->functions & OB_CLIENT_FUNC_SHADE)
        actions[num++] = OBT_PROP_ATOM(NET_WM_ACTION_SHADE);
    if (self->functions & OB_CLIENT_FUNC_CLOSE)
        actions[num++] = OBT_PROP_ATOM(NET_WM_ACTION_CLOSE);
    if (self->functions & OB_CLIENT_FUNC_MOVE)
        actions[num++] = OBT_PROP_ATOM(NET_WM_ACTION_MOVE);
    if (self->functions & OB_CLIENT_FUNC_ICONIFY)
        actions[num++] = OBT_PROP_ATOM(NET_WM_ACTION_MINIMIZE);
    if (self->functions & OB_CLIENT_FUNC_RESIZE)
        actions[num++] = OBT_PROP_ATOM(NET_WM_ACTION_RESIZE);
    if (self->functions & OB_CLIENT_FUNC_FULLSCREEN)
        actions[num++] = OBT_PROP_ATOM(NET_WM_ACTION_FULLSCREEN);
    if (self->functions & OB_CLIENT_FUNC_MAXIMIZE) {
        actions[num++] = OBT_PROP_ATOM(NET_WM_ACTION_MAXIMIZE_HORZ);
        actions[num++] = OBT_PROP_ATOM(NET_WM_ACTION_MAXIMIZE_VERT);
    }
    if (self->functions & OB_CLIENT_FUNC_ABOVE)
        actions[num++] = OBT_PROP_ATOM(NET_WM_ACTION_ABOVE);
    if (self->functions & OB_CLIENT_FUNC_BELOW)
        actions[num++] = OBT_PROP_ATOM(NET_WM_ACTION_BELOW);
    if (self->functions & OB_CLIENT_FUNC_UNDECORATE)
        actions[num++] = OBT_PROP_ATOM(OB_WM_ACTION_UNDECORATE);

    OBT_PROP_SETA32(self->window, NET_WM_ALLOWED_ACTIONS, ATOM, actions, num);


    if (!(self->functions & OB_CLIENT_FUNC_SHADE) && self->shaded) {
        if (self->frame) client_shade(self, FALSE);
        else self->shaded = FALSE;
    }
    if (!(self->functions & OB_CLIENT_FUNC_FULLSCREEN) && self->fullscreen) {
        if (self->frame) client_fullscreen(self, FALSE);
        else self->fullscreen = FALSE;
    }
    if (!(self->functions & OB_CLIENT_FUNC_MAXIMIZE) && (self->max_horz ||
                                                         self->max_vert)) {
        if (self->frame) client_maximize(self, FALSE, 0);
        else self->max_vert = self->max_horz = FALSE;
    }
}
