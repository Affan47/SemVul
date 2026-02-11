vi_enable_doorbell_aperture(struct amdgpu_device *adev,
					bool enable)
{
	u32 tmp;


	if (adev->flags & AMD_IS_APU)
		return;

	tmp = RREG32(mmBIF_DOORBELL_APER_EN);
	if (enable)
		tmp = REG_SET_FIELD(tmp, BIF_DOORBELL_APER_EN, BIF_DOORBELL_APER_EN, 1);
	else
		tmp = REG_SET_FIELD(tmp, BIF_DOORBELL_APER_EN, BIF_DOORBELL_APER_EN, 0);

	WREG32(mmBIF_DOORBELL_APER_EN, tmp);
}
