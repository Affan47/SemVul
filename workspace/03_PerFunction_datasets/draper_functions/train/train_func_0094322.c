RenderLonelyTriangles( GLUtesselator *tess, GLUface *f )
{


  GLUhalfEdge *e;
  int newState;
  int edgeState = -1;

  CALL_BEGIN_OR_BEGIN_DATA( GL_TRIANGLES );

  for( ; f != NULL; f = f->trail ) {


    e = f->anEdge;
    do {
      if( tess->flagBoundary ) {


	newState = ! e->Rface->inside;
	if( edgeState != newState ) {
	  edgeState = newState;
          CALL_EDGE_FLAG_OR_EDGE_FLAG_DATA( edgeState );
	}
      }
      CALL_VERTEX_OR_VERTEX_DATA( e->Org->data );

      e = e->Lnext;
    } while( e != f->anEdge );
  }
  CALL_END_OR_END_DATA();
}
