cmor_init_axis_def(cmor_axis_def_t *axis, int table_id)
{
  cmor_is_setup();
  axis->table_id=table_id;
  axis->climatology=0;
  axis->standard_name[0]='\0';
  axis->units[0]='\0';
  axis->axis='\0';
  axis->positive='\0';
  axis->long_name[0]='\0';
  axis->out_name[0]='\0';
  axis->type='d';
  axis->stored_direction='i';
  axis->valid_min=1.e20;
  axis->valid_max=1.e20;
  if (axis->requested!=NULL) free(axis->requested);
  axis->requested=NULL;
  if (axis->requested_bounds!=NULL) free(axis->requested_bounds);
  axis->requested_bounds=NULL;
  axis->tolerance=1.e-3;
  axis->value=1.e20;
  axis->cvalue[0]='\0';
  axis->bounds_value[0]=1.e20;
  axis->bounds_value[1]=1.e20;
  axis->convert_to[0]='\0';
  axis->formula[0]='\0';
  axis->z_factors[0]='\0';
  axis->z_bounds_factors[0]='\0';
  if (axis->crequested!=NULL) free(axis->requested);
  axis->crequested=NULL;
  axis->cname[0]='\0';
  if (axis->requested_bounds!=NULL) free(axis->requested_bounds);
  axis->requested=NULL;
  axis->n_requested=0;
  axis->n_requested_bounds=0;
  axis->index_only='n';
  axis->must_have_bounds=0;
  axis->must_call_cmor_grid=0;
}
