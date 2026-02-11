changeSticky(bool lockState)
{
	if (m_currentItem == NULL) return;
	if (m_currentItem->itemType() == ModelPart::Wire) return;

	m_currentItem->setLocalSticky(lockState);
}
