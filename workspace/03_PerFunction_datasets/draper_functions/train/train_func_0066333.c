widget_gpo_update(void *Self)
{
    WIDGET *W = (WIDGET *) Self;
    WIDGET_GPO *GPO = W->data;


    property_eval(&GPO->expression);
    property_eval(&GPO->update);


    if (W->class->draw)
	W->class->draw(W);


    if (P2N(&GPO->update) > 0) {
	timer_add_widget(widget_gpo_update, Self, P2N(&GPO->update), 1);
    }

}
