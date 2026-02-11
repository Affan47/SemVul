topResizeCallback( Widget* widget, const Event* e ) {
    if( e->type == EMousePressed ) {
        if( Widget_mouseOver( widget, &e->v ) ) {
            widget->mouseOffset.y =  e->v.y - widget->position.y;
            widget->pressed = true;
        }
    }
    if( widget->pressed && widget->mouseOffset.y != 1 ) {
        int top = e->v.y + 5 + widget->mouseOffset.y + 18;

        int size = widget->parent->parent->children[WO_Window]->position.y + widget->parent->parent->children[WO_Window]->size.y - top;
        Window_resizeUp( widget->parent->parent->children[WO_Window], size );
        if( e->type == EMouseReleased )
            widget->pressed = false;

        return true;
    }
    else {
        widget->mouseOffset.y = 1;
        return false;
    }
}
