gog_reg_curve_view_size_allocate (GogView *view, GogViewAllocation const *allocation)
{
	GSList *ptr;

	for (ptr = view->children; ptr != NULL; ptr = ptr->next)
		gog_view_size_allocate (GOG_VIEW (ptr->data), allocation);
	(reg_curve_view_parent_klass->size_allocate) (view, allocation);
}
