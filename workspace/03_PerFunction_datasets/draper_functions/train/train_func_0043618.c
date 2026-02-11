isBlocked()
{
    DebugWindow* self = window();
    if (!self)
        return false;
    return self->inSession() || self->m_modalLevel;
}
