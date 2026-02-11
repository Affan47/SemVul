copyToScaling(IImage* target)
{
	if (!target)
		return;

	const core::dimension2d<u32>& targetSize = target->getDimension();

	if (targetSize==Size)
	{
		copyTo(target);
		return;
	}

	copyToScaling(target->lock(), targetSize.Width, targetSize.Height, target->getColorFormat());
	target->unlock();
}
