CreateCubicPrism(double x1,double x2,double y1,double y2,double z1,double z2)	{
	vector<TPoint3D> verts;
	vector<TPolyhedronFace> faces;
	for (int i=0;i<8;i++) verts.push_back(TPoint3D((i&1)?x2:x1,(i&2)?y2:y1,(i&4)?z2:z1));
	static uint32_t faceVertices[]={0,1,5,4, 2,3,7,6, 0,2,6,4, 1,3,7,5, 0,1,3,2, 4,5,7,6};
	TPolyhedronFace f;
	for (uint32_t *p=reinterpret_cast<uint32_t *>(&faceVertices);p<24+reinterpret_cast<uint32_t *>(&faceVertices);p+=4)	{
		f.vertices.insert(f.vertices.begin(),p,p+4);
		faces.push_back(f);
		f.vertices.clear();
	}
	return CreateNoCheck(verts,faces);
}
