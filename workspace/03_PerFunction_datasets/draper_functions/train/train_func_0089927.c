resizeEdgeStorage()
    {

        Edge* newEdges = new Edge[numAllocatedEdges_];


        edges_ = newEdges;


		allEdges_.add(newEdges);


		edgeCount_ = 0;
    }
