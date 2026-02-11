_dxf_callDisplayListOGL(dxObject dlo)
{
	if (dlo)
	{
		DXDisplayListOGL *dl = (DXDisplayListOGL *)DXGetPrivateData((Private)dlo);
	    if (dl)
			glCallList(dl->list);
	}
}
