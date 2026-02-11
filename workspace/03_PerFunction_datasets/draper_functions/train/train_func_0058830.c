unregisterIconset(const Iconset *i)
{
	if (iconsets_ && iconsets_->contains((Iconset*)i))
		iconsets_->removeAll((Iconset*)i);
}
