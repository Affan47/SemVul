radeon_irq_kms_pflip_irq_put(struct radeon_device *rdev, int crtc)
{
	unsigned long irqflags;

	if (crtc < 0 || crtc >= rdev->num_crtc)
		return;

	if (!rdev->ddev->irq_enabled)
		return;

	if (atomic_dec_and_test(&rdev->irq.pflip[crtc])) {
		spin_lock_irqsave(&rdev->irq.lock, irqflags);
		radeon_irq_set(rdev);
		spin_unlock_irqrestore(&rdev->irq.lock, irqflags);
	}
}
