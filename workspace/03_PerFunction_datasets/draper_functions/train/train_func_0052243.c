window1Callback( Widget* widget, const Event* e ) {
    if( Widget_mouseOver( widget, &e->v ) )
        if( e->type == EMousePressed || e->type == EMouseReleased )
            return true;
}
