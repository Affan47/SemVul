setLogicalSize(const QSizeF& size)
{
	if (size.isValid() && d->m_logicalSize != size)
	{
		d->m_logicalSize = size;
		d->_k_update();
	}
}
