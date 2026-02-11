elm_5node_quad_triangulate( geometry_t *geom,element_t *Elm )
{
    triangle_t triangle;

    triangle.Element = Elm;

    triangle.v[0] = Elm->Topology[0];
    triangle.v[1] = Elm->Topology[1];
    triangle.v[2] = Elm->Topology[4];

    triangle.Edge[0] = TRUE;
    triangle.Edge[1] = FALSE;
    triangle.Edge[2] = FALSE;

    if ( !geo_add_triangle( geom,&triangle ) )  return FALSE;

    triangle.v[0] = Elm->Topology[1];
    triangle.v[1] = Elm->Topology[2];
    triangle.v[2] = Elm->Topology[4];

    triangle.Edge[0] = TRUE;
    triangle.Edge[1] = FALSE;
    triangle.Edge[2] = FALSE;

    if ( !geo_add_triangle( geom,&triangle ) )  return FALSE;

    triangle.v[0] = Elm->Topology[2];
    triangle.v[1] = Elm->Topology[3];
    triangle.v[2] = Elm->Topology[4];

    triangle.Edge[0] = TRUE;
    triangle.Edge[1] = FALSE;
    triangle.Edge[2] = FALSE;

    if ( !geo_add_triangle( geom,&triangle ) )  return FALSE;

    triangle.v[0] = Elm->Topology[3];
    triangle.v[1] = Elm->Topology[0];
    triangle.v[2] = Elm->Topology[4];

    triangle.Edge[0] = TRUE;
    triangle.Edge[1] = FALSE;
    triangle.Edge[2] = FALSE;

    if ( !geo_add_triangle( geom,&triangle ) )  return FALSE;

    return TRUE;
}
