Window_resizeLeft( Widget* widget, int size ) {
    if( size < widget->minSize.x )
        size = widget->minSize.x;

    Widget* head = widget->parent;
    Widget* outline = widget->parent->children[WO_Outline];
    Widget_resize( head, &(vec2i){ size, 17 } );
    Widget_setPosition( head, &(vec2i){ widget->position.x + widget->size.x - size, widget->position.y - 18 } );
    Widget_resize( outline, &(vec2i){ size + 10, widget->size.y + head->size.y + 11 } );
    Widget_setPosition( outline, &(vec2i){ head->position.x - 5, head->position.y - 5 } );
    Widget_resize( outline->children[WO_Bottom], &(vec2i){ size, 5 } );
    Widget_setPosition( outline->children[WO_Bottom], &(vec2i){ head->position.x, widget->position.y + widget->size.y } );
    Widget_resize( outline->children[WO_Top], &(vec2i){ size, 5 } );
    Widget_setPosition( outline->children[WO_Top], &(vec2i){ head->position.x, head->position.y - 5 } );


    Widget_setPosition( outline->children[WO_TopRight], &(vec2i){ outline->position.x + outline->size.x - 5, outline->position.y } );
    Widget_setPosition( outline->children[WO_Right], &(vec2i){ outline->position.x + outline->size.x - 5, outline->position.y + 5 } );
    Widget_setPosition( outline->children[WO_BottomRight], &(vec2i){ outline->position.x + outline->size.x - 5, outline->position.y + outline->size.y - 5 } );
    Widget_setPosition( head->children[WO_Cross], &(vec2i){ head->position.x + head->size.x - 13, head->position.y + 3 } );
    Widget_setPosition( head->children[WO_Icon], &(vec2i){ head->position.x + 3, head->position.y + 3 } );

    Widget_resize( widget, &(vec2i){ size, widget->size.y } );
    Widget_setPosition( widget, &(vec2i){ head->position.x, head->position.y + 18 } );
}
