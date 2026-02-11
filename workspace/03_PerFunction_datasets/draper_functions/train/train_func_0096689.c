augment(double height) const	{
	size_t NV=mVertices.size();
	size_t NF=mFaces.size();
	vector<TPoint3D> vertices(NV+NF);
	std::copy(mVertices.begin(),mVertices.end(),vertices.begin());
	size_t tnf=0;
	for (vector<TPolyhedronFace>::const_iterator it=mFaces.begin();it!=mFaces.end();++it) tnf+=it->vertices.size();
	vector<TPolyhedronFace> faces(tnf);
	TPolygon3D tmp;
	TPlane pTmp;
	TPoint3D cTmp;
	size_t iF=0;
	TPoint3D phCenter;
	getCenter(phCenter);
	TPolyhedronFace fTmp;
	fTmp.vertices.resize(3);
	for (size_t i=0;i<NF;i++)	{
		TPoint3D &vertex=vertices[NV+i];
		const vector<uint32_t> &face=mFaces[i].vertices;
		size_t N=face.size();
		tmp.resize(N);
		for (size_t j=0;j<N;j++) tmp[j]=mVertices[face[j]];
		tmp.getBestFittingPlane(pTmp);
		pTmp.unitarize();
		tmp.getCenter(cTmp);
		if (pTmp.evaluatePoint(phCenter)>0)	for (size_t j=0;j<3;j++) vertex[j]=cTmp[j]-height*pTmp.coefs[j];
		else for (size_t j=0;j<3;j++) vertex[j]=cTmp[j]+height*pTmp.coefs[j];
		fTmp.vertices[0]=NV+i;
		for (size_t j=0;j<N;j++)	{
			fTmp.vertices[1]=face[j];
			fTmp.vertices[2]=face[(j+1)%N];
			faces[iF+j]=fTmp;
		}
		iF+=N;
	}
	return CreateNoCheck(vertices,faces);
}
