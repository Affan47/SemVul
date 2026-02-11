set_f_phase_density(f_id)
facet_id f_id;
{
  int i = get_b_phase(get_facet_body(f_id));
  int j = get_b_phase(get_facet_body(inverse_id(f_id)));
  set_attr(f_id,DENSITY);
  set_facet_density(f_id,phase_data[i][j]);
}
