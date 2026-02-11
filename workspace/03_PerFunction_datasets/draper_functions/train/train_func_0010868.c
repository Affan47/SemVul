ReadVRTS(){
	_vflags=ReadInt();
	_tcsets=ReadInt();
	_tcsize=ReadInt();
	if( _tcsets<0 || _tcsets>4 || _tcsize<0 || _tcsize>4 ){
		Fail( "Bad texcoord data" );
	}

	int sz=12+(_vflags&1?12:0)+(_vflags&2?16:0)+(_tcsets*_tcsize*4);
	int n_verts=ChunkSize()/sz;

	int v0=_vertices.size();
	_vertices.resize( v0+n_verts );

	for( int i=0;i<n_verts;++i ){
		Vertex &v=_vertices[v0+i];

		memset( v.bones,0,sizeof(v.bones) );
		memset( v.weights,0,sizeof(v.weights) );

		v.vertex=ReadVec3();

		if( _vflags & 1 ) v.normal=ReadVec3();

		if( _vflags & 2 ) ReadQuat();

		for( int i=0;i<_tcsets;++i ){
			float t[4]={0,0,0,0};
			for( int j=0;j<_tcsize;++j ){
				t[j]=ReadFloat();
			}
			t[1]=1-t[1];
			if( !i ) v.texcoords=aiVector3D( t[0],t[1],t[2] );
		}
	}
}
