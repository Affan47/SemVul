output_wkb_point(uchar* geom)
{
	if ( lwgi ){
		write_wkb_bytes(geom,dims,4);
		return geom + (4*dims);
	}
	else{
		write_wkb_bytes(geom,dims,8);
		return geom + (8*dims);
	}
}
