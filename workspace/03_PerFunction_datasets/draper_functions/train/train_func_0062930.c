etgl_item_is_editing_changed_cb (ETableItem *item,
                                 GParamSpec *param,
                                 ETableGroupLeaf *etgl)
{
	g_return_if_fail (E_IS_TABLE_GROUP_LEAF (etgl));

	g_object_notify (G_OBJECT (etgl), "is-editing");
}
