vmw_view_cotable_list_destroy(struct vmw_private *dev_priv,
				   struct list_head *list,
				   bool readback)
{
	struct vmw_view *entry, *next;

	WARN_ON_ONCE(!mutex_is_locked(&dev_priv->binding_mutex));

	list_for_each_entry_safe(entry, next, list, cotable_head)
		WARN_ON(vmw_view_destroy(&entry->res));
}
