radeon_vce_fini(struct radeon_device *rdev)
{
	if (rdev->vce.vcpu_bo == NULL)
		return;

	radeon_bo_unref(&rdev->vce.vcpu_bo);

	release_firmware(rdev->vce_fw);
}
