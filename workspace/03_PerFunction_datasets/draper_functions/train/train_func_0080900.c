on_adjust_all_meshes_activate          (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  int lp=MAIN_WIN-1;
  for(; lp>=0; lp--) {
    if( sp->im_widget[lp] != NULL)
      {
	int xi, yi;
	MeshT *mesh=&(sp->im_mesh[lp]);
	GdkPixbuf   *dst= (sp->im_warped_pixbuf[lp]);
	for(xi=0; xi < mesh->nx ; xi++) {
	  for(yi=0; yi<mesh->ny  ; yi++) {
	    if( 0 !=  meshGetLabel(mesh,xi,yi)) {
	      adjust_1_point_wrt_morph(mesh,dst ,  xi, yi);
	    }
	  }
	}
	MY_GTK_DRAW(sp->im_widget[lp]);
      }
  }
}
