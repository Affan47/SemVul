client_setup_decor_and_functions(ObClient *self, gboolean reconfig)
{
    client_setup_default_decor_and_functions(self);

    client_setup_decor_undecorated(self);

    if (self->max_horz && self->max_vert) {


        self->decorations &= ~(OB_FRAME_DECOR_HANDLE | OB_FRAME_DECOR_GRIPS);
    }


    if (!(self->decorations & OB_FRAME_DECOR_TITLEBAR))
        self->functions &= ~OB_CLIENT_FUNC_SHADE;


    if (self->fullscreen) {
        self->functions &= (OB_CLIENT_FUNC_CLOSE |
                            OB_CLIENT_FUNC_FULLSCREEN |
                            OB_CLIENT_FUNC_ICONIFY);
        self->decorations = 0;
    }

    client_change_allowed_actions(self);

    if (reconfig)

        client_reconfigure(self, FALSE);
}
