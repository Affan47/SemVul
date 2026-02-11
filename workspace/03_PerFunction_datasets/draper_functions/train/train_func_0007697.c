wait_smu_response(struct amdgpu_device *adev)
{
	int i;
	uint32_t val;

	for (i = 0; i < adev->usec_timeout; i++) {
		val = RREG32(mmSMC_RESP_0);
		if (REG_GET_FIELD(val, SMC_RESP_0, SMC_RESP))
			break;
		udelay(1);
	}

	if (i == adev->usec_timeout)
		return -EINVAL;

	return 0;
}
