key_press_cb (GocCanvas *canvas, GdkEventKey* event, G_GNUC_UNUSED gpointer data)
{
	return (canvas->grabbed_item != NULL)?
		GOC_ITEM_GET_CLASS (canvas->grabbed_item)->key_pressed (canvas->grabbed_item, event): FALSE;
}
