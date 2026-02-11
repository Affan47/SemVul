bottomRightResizeCallback( Widget* widget, const Event* e ) {
    if( Widget_mouseOver( widget, &e->v ) ) {
        if( e->type == EMousePressed ) {
            widget->mouseOffset = vec2i_sub( &e->v, &widget->position );
            widget->pressed = true;
        }
    }
    if( widget->pressed && widget->mouseOffset.x != -1 ) {
        vec2i bottomright = vec2i_sub( &e->v, &widget->mouseOffset );

        vec2i size = vec2i_sub( &bottomright, &widget->parent->parent->children[WO_Window]->position );
        Window_resizeRight( widget->parent->parent->children[WO_Window], size.x );
        Window_resizeDown( widget->parent->parent->children[WO_Window], size.y );
        if( e->type == EMouseReleased )
            widget->pressed = false;

        return true;
    }
    else {
        widget->mouseOffset = vec2i_c( -1, -1 );
        return false;
    }
}
