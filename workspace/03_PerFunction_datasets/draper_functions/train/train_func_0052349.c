cb_tess_conic_to( FT_Vector * ctrl, FT_Vector * to, void * user )
{
    VMvect vi,vf,vc, v;
    VMfloat t, dt;
    struct TessData * data = (struct TessData *) user;

    dt=1.0/data->points_per_spline;

    vi=vec_xyz( data->from.x, data->from.y, 0.0 );
    vf=vec_xyz( to->x, to->y, 0.0 );
    vc=vec_xyz( ctrl->x, ctrl->y, 0.0 );

    for(t=0.0;t<1.0+dt/2.0;t+=dt){
        v=conic_spline_point(vi, vf, vc, t);
        tess_add_point(v, data, 0);
    }

    data->from=*to;
    return 0;
}
