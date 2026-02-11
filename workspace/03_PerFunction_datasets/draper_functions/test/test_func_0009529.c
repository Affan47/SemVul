radeon_kfd_device_probe(struct radeon_device *rdev)
{
	if (kgd2kfd)
		rdev->kfd = kgd2kfd->probe((struct kgd_dev *)rdev,
			rdev->pdev, &kfd2kgd);
}
