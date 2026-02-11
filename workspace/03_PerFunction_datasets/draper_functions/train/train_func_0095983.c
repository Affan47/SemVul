_cmsAdaptMatrixToD50(cmsMAT3* r, const cmsCIExyY* SourceWhitePt)
{
	cmsCIEXYZ Dn;
	cmsMAT3 Bradford;
	cmsMAT3 Tmp;

	cmsxyY2XYZ(&Dn, SourceWhitePt);

	if (!_cmsAdaptationMatrix(&Bradford, NULL, &Dn, cmsD50_XYZ())) return FALSE;

	Tmp = *r;
	_cmsMAT3per(r, &Bradford, &Tmp);

	return TRUE;
}
