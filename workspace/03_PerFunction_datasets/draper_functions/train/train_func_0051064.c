pwm_channel_update_output(Pwm *p_pwm, pwm_channel_t *p_channel,
		pwm_output_t *p_output, bool b_sync)
{
	uint32_t ch_num = p_channel->channel;
	uint32_t channel = (1 << ch_num);

	bool override_pwmh = p_output->b_override_pwmh;
	bool override_pwml = p_output->b_override_pwml;
	uint32_t pwmh = p_output->override_level_pwmh;
	uint32_t pwml = p_output->override_level_pwml;


	p_channel->output_selection.b_override_pwmh = override_pwmh;
	p_channel->output_selection.b_override_pwml = override_pwml;
	p_channel->output_selection.override_level_pwmh = (pwm_level_t) pwmh;
	p_channel->output_selection.override_level_pwml = (pwm_level_t) pwml;


	uint32_t override_value = p_pwm->PWM_OOV;
	override_value &= ~((PWM_OOV_OOVH0 | PWM_OOV_OOVL0) << ch_num);
	override_value |= (((pwml << 16) | pwmh) << ch_num);
	p_pwm->PWM_OOV = override_value;


	if (override_pwml && override_pwmh) {
		b_sync ? (p_pwm->PWM_OSSUPD =
				(channel | (channel << 16))) : (p_pwm->PWM_OSS =
				(channel | (channel << 16)));
	} else {
		b_sync ? (p_pwm->PWM_OSCUPD =
				(channel | (channel << 16))) : (p_pwm->PWM_OSC =
				(channel | (channel << 16)));
	}
}
