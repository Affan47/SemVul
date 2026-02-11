widget_timer_update(void *Self)
{
    WIDGET *W = (WIDGET *) Self;
    WIDGET_TIMER *Timer = W->data;
    int update, active;


    property_eval(&Timer->update);
    property_eval(&Timer->active);


    update = P2N(&Timer->update);
    if (update < 10)
	update = 10;


    active = P2N(&Timer->active);
    if (active > 0) {
	property_eval(&Timer->expression);
    }


    timer_add(widget_timer_update, Self, update, 1);
}
