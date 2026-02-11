currentDesktop( bool ignore_viewport ) const {
    if( !ignore_viewport && KWindowSystem::mapViewport())
        return KWindowSystem::currentDesktop();
    return p->current_desktop == 0 ? 1 : p->current_desktop;
}
