RootWidget_init() {
    check( game, "Can't init widget without running game.\n" );
    RootWidget* rootWidget = byte_alloc( sizeof( RootWidget ) );
    if( rootWidget ) {
        rootWidget->keyListener = rootKeyListener;
        rootWidget->mouseListener = rootMouseListener;
        rootWidget->mouseDown = false;
        EventManager_addListener( LT_MouseListener, rootWidget->mouseListener, rootWidget );
        EventManager_addListener( LT_KeyListener, rootWidget->keyListener, rootWidget );
        vec2i size = Context_getSize();
        rootWidget->widget = Widget_init( WT_Root, &size, NULL, NULL, -1 );
    }
    return rootWidget;
error :
    return NULL;
}
