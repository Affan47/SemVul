PyFFContour_Str(PyFF_Contour *self) {
    char *buffer, *pt;
    int i;
    PyObject *ret;

    buffer=pt=galloc(self->pt_cnt*30+30);
    strcpy(buffer, self->is_quadratic? "<Contour(quadratic)\n":"<Contour(cubic)\n");
    pt = buffer+strlen(buffer);
    for ( i=0; i<self->pt_cnt; ++i ) {
	sprintf( pt, "  (%g,%g) %s\n", self->points[i]->x, self->points[i]->y,
		self->points[i]->on_curve ? "on" : "off" );
	pt += strlen( pt );
    }
    strcpy(pt,">");
    ret = STRING_TO_PY( buffer );
    free( buffer );
return( ret );
}
