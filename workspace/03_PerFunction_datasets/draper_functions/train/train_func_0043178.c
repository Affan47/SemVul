__gl_renderBoundary( GLUtesselator *tess, GLUmesh *mesh )
{
  GLUface *f;
  GLUhalfEdge *e;

  for( f = mesh->fHead.next; f != &mesh->fHead; f = f->next ) {
    if( f->inside ) {
      CALL_BEGIN_OR_BEGIN_DATA( GL_LINE_LOOP );
      e = f->anEdge;
      do {
        CALL_VERTEX_OR_VERTEX_DATA( e->Org->data );
	e = e->Lnext;
      } while( e != f->anEdge );
      CALL_END_OR_END_DATA();
    }
  }
}
