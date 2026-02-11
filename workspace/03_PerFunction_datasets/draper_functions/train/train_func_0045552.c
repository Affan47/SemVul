collectLineEdge(DirectedEdge *de, OverlayOp::OpCode opCode,
		vector<Edge*> *edges)
{


  if (de->isLineEdge()) {

    const Label& label = de->getLabel();

    Edge *e = de->getEdge();

    if (!de->isVisited()
          && OverlayOp::isResultOfOp(label, opCode)
          && !e->isCovered() )
		{


			edges->push_back(e);
			de->setVisitedEdge(true);
		}

	}

}
