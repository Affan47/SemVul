kv_dpm_powergate_vce(struct radeon_device *rdev, bool gate)
{
	struct kv_power_info *pi = kv_get_pi(rdev);

	if (pi->vce_power_gated == gate)
		return;

	pi->vce_power_gated = gate;

	if (gate) {
		if (pi->caps_vce_pg) {

			kv_notify_message_to_smu(rdev, PPSMC_MSG_VCEPowerOFF);
		}
	} else {
		if (pi->caps_vce_pg) {
			kv_notify_message_to_smu(rdev, PPSMC_MSG_VCEPowerON);
			vce_v2_0_resume(rdev);
			vce_v1_0_start(rdev);
		}
	}
}
