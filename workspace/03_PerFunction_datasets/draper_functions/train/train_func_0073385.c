elm_4node_triangle_triangulate( geometry_t *geom, element_t *Elm, element_t *Parent)
{
    double u,v,w,s;

    int i,j;

    triangle_t triangle;

    triangle.Element = Parent;
    for( i=0; i<3; i++ )
    {
        triangle.v[i] = Elm->Topology[i];
        triangle.Edge[i] = TRUE;
    }
    geo_triangle_normal( geom,&triangle );

    return geo_add_triangle( geom, &triangle );
}
