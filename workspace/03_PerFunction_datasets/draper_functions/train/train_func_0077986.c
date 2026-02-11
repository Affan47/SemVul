widget_image_update(void *Self)
{
    WIDGET *W = (WIDGET *) Self;
    WIDGET_IMAGE *Image = W->data;


    if (W->parent == NULL) {


	property_eval(&Image->file);
	property_eval(&Image->update);
	property_eval(&Image->reload);
	property_eval(&Image->visible);
	property_eval(&Image->inverted);


	widget_image_render(W->name, Image);

    }


    if (W->class->draw)
	W->class->draw(W);


    if (P2N(&Image->update) > 0) {
	timer_add_widget(widget_image_update, Self, P2N(&Image->update), 1);
    }
}
