bluetooth_agent_set_confirm_func(BluetoothAgent *agent,
				BluetoothAgentConfirmFunc func, gpointer data)
{
	BluetoothAgentPrivate *priv;

	g_return_if_fail (BLUETOOTH_IS_AGENT (agent));

	priv = BLUETOOTH_AGENT_GET_PRIVATE(agent);

	priv->confirm_func = func;
	priv->confirm_data = data;
}
