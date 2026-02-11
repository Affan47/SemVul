PyFFLayer_Str(PyFF_Layer *self) {
    char *buffer, *pt;
    int cnt, i,j;
    PyFF_Contour *contour;
    PyObject *ret;

    cnt = 0;
    for ( i=0; i<self->cntr_cnt; ++i )
	cnt += self->contours[i]->pt_cnt;
    buffer=pt=galloc(cnt*30+self->cntr_cnt*30+30);
    strcpy(buffer, self->is_quadratic? "<Layer(quadratic)\n":"<Layer(cubic)\n");
    pt = buffer+strlen(buffer);
    for ( i=0; i<self->cntr_cnt; ++i ) {
	contour = self->contours[i];
	strcpy(pt, " <Contour\n" );
	pt += strlen(pt);
	for ( j=0; j<contour->pt_cnt; ++j ) {
	    sprintf( pt, "  (%g,%g) %s\n", contour->points[j]->x, contour->points[j]->y,
		    contour->points[j]->on_curve ? "on" : "off" );
	    pt += strlen( pt );
	}
	strcpy(pt," >\n");
	pt += strlen(pt);
    }
    strcpy(pt,">");
    ret = STRING_TO_PY( buffer );
    free( buffer );
return( ret );
}
