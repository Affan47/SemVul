add_5tuple( ntuple_list out, double v1, double v2,
                 double v3, double v4, double v5 )
{

  if( out == NULL ) error("add_5tuple: invalid n-tuple input.");
  if( out->dim != 5 ) error("add_5tuple: the n-tuple must be a 5-tuple.");


  if( out->size == out->max_size ) enlarge_ntuple_list(out);
  if( out->values == NULL ) error("add_5tuple: invalid n-tuple input.");


  out->values[ out->size * out->dim + 0 ] = v1;
  out->values[ out->size * out->dim + 1 ] = v2;
  out->values[ out->size * out->dim + 2 ] = v3;
  out->values[ out->size * out->dim + 3 ] = v4;
  out->values[ out->size * out->dim + 4 ] = v5;


  out->size++;
}
