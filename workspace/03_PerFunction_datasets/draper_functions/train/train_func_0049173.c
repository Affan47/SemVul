listMess(int argc, t_atom*argv) {
	if(0==m_numInputs) {
		if(argc%3) {
			error("list must contain 3 elements for each vertex!");
			return;
		}
		createVertices(argc/3);
	}

	if(m_numVertices*3==argc) {
		int i=0;
		for(i=0; i<m_numVertices; i++) {
			setVert(i,
							atom_getfloat(argv+0),
							atom_getfloat(argv+1),
							atom_getfloat(argv+2)
							);
			argv+=3;
		}
	} else {
		error("vertex-list must have exactly %d numbers", m_numVertices*3);
	}
}
