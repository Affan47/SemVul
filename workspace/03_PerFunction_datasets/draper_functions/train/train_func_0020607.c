ganv_item_invoke_update(GanvItem* item, int flags)
{
	int child_flags = flags;


	child_flags &= ~GANV_CANVAS_BASE_UPDATE_REQUESTED;

	if (item->object.flags & GANV_ITEM_NEED_UPDATE) {
		child_flags |= GANV_CANVAS_BASE_UPDATE_REQUESTED;
	}

	if (item->object.flags & GANV_ITEM_NEED_VIS) {
		child_flags |= GANV_CANVAS_BASE_UPDATE_VISIBILITY;
	}

	if (child_flags & GCI_UPDATE_MASK) {
		if (GANV_ITEM_GET_CLASS(item)->update) {
			GANV_ITEM_GET_CLASS(item)->update(item, child_flags);
		}
	}
}
