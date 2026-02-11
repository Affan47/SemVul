item_adjust( Item *item )
{

    item->nx = 0; item->ny = item->h / 2; item->nalign = STK_FONT_ALIGN_LEFT | STK_FONT_ALIGN_CENTER_Y;
    if ( item->type == ITEM_LINK || item->type == ITEM_ACTION || item->type == ITEM_SEPARATOR ) {
        item->nx = item->w / 2;
        item->nalign = STK_FONT_ALIGN_CENTER_X | STK_FONT_ALIGN_CENTER_Y;
    }
    item->vx = item->w - 1; item->vy = item->h / 2; item->valign = STK_FONT_ALIGN_RIGHT | STK_FONT_ALIGN_CENTER_Y;

    if ( item->hint )
        hint_set_pos( item->hint, item->x + item->w * 0.6, item->y );
}
