getColorAnnotation(fp_Page * pPage,UT_uint32 pid) const
{

	UT_uint32 pos = pPage->getAnnotationPos(pid);
	if(pos > 9)
		pos = 9;
	return m_colorAnnotations[pos];
}
