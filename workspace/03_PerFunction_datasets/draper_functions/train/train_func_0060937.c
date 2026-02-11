mesh_normalize_variance(MeshT *mesh,const int anykind,
			     const struct  mesh_variance_s bef,
			     const struct  mesh_variance_s aft )
{
  int xi,yi;
  double x,y, bef_l=__deter__(bef), aft_l= __deter__(aft),
    lx= sqrt(bef_l/aft_l), ly=lx;

  for(xi=0; xi < mesh->nx ; xi++) {
    for(yi=0; yi<mesh->ny  ; yi++) {
      if( anykind || 0 ==  meshGetLabel(mesh,xi,yi)) {
	x=meshGetx(mesh, xi,yi) *lx -aft.mx *lx + aft.mx ;
	y=meshGety(mesh, xi,yi) *ly -aft.my *ly + aft.my;
	meshSetNoundo(mesh,xi,yi,x,y);
      }
    }
  }
}
