set_item_color(struct inst *inst, const char *color)
{
	GtkWidget *label;

	if (inst->vec)
		label = inst->vec->list_widget;
	else
		label = inst->obj->list_widget;
	if (label)
		label_in_box_bg(box_of_label(label), color);
}
