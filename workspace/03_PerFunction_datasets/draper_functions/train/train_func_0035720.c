pan_flower_build(PanWindow *pw, FlowerGroup *group, FlowerGroup *parent)
{
	GList *work;
	gint x, y;

	if (!group) return;

	if (parent && parent->children)
		{
		pan_flower_position(group, parent, &x, &y);
		}
	else
		{
		x = 0;
		y = 0;
		}

	pan_flower_move(group, x, y);

	if (parent)
		{
		PanItem *pi;
		gint px, py, gx, gy;
		gint x1, y1, x2, y2;

		px = parent->x + parent->width / 2;
		py = parent->y + parent->height / 2;

		gx = group->x + group->width / 2;
		gy = group->y + group->height / 2;

		x1 = MIN(px, gx);
		y1 = MIN(py, gy);

		x2 = MAX(px, gx + 5);
		y2 = MAX(py, gy + 5);

		pi = pan_item_tri_new(pw, NULL, x1, y1, x2 - x1, y2 - y1,
				      px, py, gx, gy, gx + 5, gy + 5,
				      255, 40, 40, 128);
		pan_item_tri_border(pi, PAN_BORDER_1 | PAN_BORDER_3,
				    255, 0, 0, 128);
		}

	pw->list = g_list_concat(group->items, pw->list);
	group->items = NULL;

	group->circumference = 0;
	work = group->children;
	while (work)
		{
		FlowerGroup *child;

		child = work->data;
		work = work->next;

		group->circumference += child->diameter;
		}

	work = g_list_last(group->children);
	while (work)
		{
		FlowerGroup *child;

		child = work->data;
		work = work->prev;

		pan_flower_build(pw, child, group);
		}

	g_list_free(group->children);
	g_free(group);
}
