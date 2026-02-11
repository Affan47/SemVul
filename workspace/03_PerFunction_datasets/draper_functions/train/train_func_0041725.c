ganv_group_bounds(GanvItem* item, double* x1, double* y1, double* x2, double* y2)
{
	GanvGroup* group;
	GanvItem*  child;
	GList*     list;
	double     tx1, ty1, tx2, ty2;
	double     minx, miny, maxx, maxy;
	int        set;

	group = GANV_GROUP(item);


	child = NULL;

	set = FALSE;

	for (list = group->item_list; list; list = list->next) {
		child = (GanvItem*)list->data;

		if (child->object.flags & GANV_ITEM_VISIBLE) {
			set = TRUE;
			ganv_item_get_bounds(child, &minx, &miny, &maxx, &maxy);
			break;
		}
	}


	if (!set) {
		*x1 = *y1 = *x2 = *y2 = 0.0;
		return;
	}


	list = list->next;

	for (; list; list = list->next) {
		child = (GanvItem*)list->data;

		if (!(child->object.flags & GANV_ITEM_VISIBLE)) {
			continue;
		}

		ganv_item_get_bounds(child, &tx1, &ty1, &tx2, &ty2);

		if (tx1 < minx) {
			minx = tx1;
		}

		if (ty1 < miny) {
			miny = ty1;
		}

		if (tx2 > maxx) {
			maxx = tx2;
		}

		if (ty2 > maxy) {
			maxy = ty2;
		}
	}

	*x1 = minx;
	*y1 = miny;
	*x2 = maxx;
	*y2 = maxy;
}
