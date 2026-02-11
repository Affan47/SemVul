_abi_widget_unbindListener(AbiWidget *widget)
{

	AbiPrivData * private_data = (AbiPrivData *)widget->priv;
	AbiWidget_ViewListener * pListener = private_data->m_pViewListener;
	if (!pListener)
		return;

	pListener->unbind();
}
