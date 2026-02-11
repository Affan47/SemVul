getHdrFtrLayout(void)
{
	fl_ContainerLayout * pCL = this;
	while(pCL && (pCL->getContainerType() != FL_CONTAINER_HDRFTR) &&
		  (pCL->getContainerType() != FL_CONTAINER_DOCSECTION))
	{
		pCL = pCL->myContainingLayout();
	}
	if(pCL && (pCL->getContainerType() ==  FL_CONTAINER_HDRFTR))
	{
		return static_cast<fl_HdrFtrSectionLayout *>(pCL);
	}
	return NULL;
}
