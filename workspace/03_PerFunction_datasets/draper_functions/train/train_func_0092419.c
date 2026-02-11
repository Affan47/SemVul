leftResizeCallback( Widget* widget, const Event* e ) {
    if( e->type == EMousePressed ) {
        if( Widget_mouseOver( widget, &e->v ) ) {
            widget->mouseOffset.x =  widget->position.x - e->v.x;
            widget->pressed = true;
        }
    }

    if( widget->pressed && widget->mouseOffset.x != 1 ) {
        int left = e->v.x + 5 + widget->mouseOffset.x;

        int size = widget->parent->parent->children[WO_Window]->position.x + widget->parent->parent->children[WO_Window]->size.x - left;
        Window_resizeLeft( widget->parent->parent->children[WO_Window], size );
        if( e->type == EMouseReleased )
            widget->pressed = false;

        return true;
    }
    else {
        widget->mouseOffset.x = 1;
        return false;
    }
}
