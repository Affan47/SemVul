getNextContainerInSection(void) const
{
	if (getNext())
	{
		return static_cast<fp_Container *>(getNext());
	}

	fl_ContainerLayout* pNextBlock = m_pBlock->getNext();
	while(pNextBlock &&
		  ((pNextBlock->getContainerType() == FL_CONTAINER_ENDNOTE) ||
		   (pNextBlock->getContainerType() == FL_CONTAINER_FRAME) ||
		  (pNextBlock->isHidden() == FP_HIDDEN_FOLDED)))
	{
		pNextBlock = pNextBlock->getNext();
	}
	if (pNextBlock)
	{
		return static_cast<fp_Container *>(pNextBlock->getFirstContainer());
	}
	return NULL;
}
