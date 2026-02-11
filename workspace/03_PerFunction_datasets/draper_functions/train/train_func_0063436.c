adc_msg_terminate(struct adc_message* cmd)
{
	if (cmd->cache[cmd->length - 1] != '\n')
	{
		adc_msg_cache_append(cmd, "\n", 1);
	}
	ADC_MSG_ASSERT(cmd);
}
