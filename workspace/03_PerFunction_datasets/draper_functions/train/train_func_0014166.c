_abi_widget_releaseListener(AbiWidget *widget)
{

	AbiPrivData * private_data = (AbiPrivData *)widget->priv;
	if (!private_data->m_pViewListener)
		return;

	DELETEP(private_data->m_pViewListener);
	private_data->m_pViewListener = 0;
}
