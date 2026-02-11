_cmsGetTagTrueType(cmsHPROFILE hProfile, cmsTagSignature sig)
{
	_cmsICCPROFILE* Icc = (_cmsICCPROFILE*) hProfile;
	cmsTagTypeHandler* TypeHandler;
	int n;


	n = _cmsSearchTag(Icc, sig, TRUE);
	if (n < 0) return (cmsTagTypeSignature) 0;


	TypeHandler =  Icc -> TagTypeHandlers[n];
	return TypeHandler ->Signature;
}
