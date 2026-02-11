client_get_startup_id(ObClient *self)
{
    if (!(OBT_PROP_GETS_UTF8(self->window, NET_STARTUP_ID, &self->startup_id)))
        if (self->group)
            OBT_PROP_GETS_UTF8(self->group->leader, NET_STARTUP_ID,
                               &self->startup_id);
}
