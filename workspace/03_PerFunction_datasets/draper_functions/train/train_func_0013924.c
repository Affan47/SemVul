xsh_frame_set_shiftifu_ref( cpl_propertylist *header,
  cpl_frame *shift_frame)
{
  cpl_propertylist *shift_header = NULL;
  const char *shift_name = NULL;
  double waveref, slitref;

  XSH_ASSURE_NOT_NULL( header);
  XSH_ASSURE_NOT_NULL( shift_frame);

  check( shift_name = cpl_frame_get_filename( shift_frame));
  check( shift_header = cpl_propertylist_load( shift_name, 0));

  check( waveref = xsh_pfits_get_shiftifu_lambdaref( shift_header));
  check( slitref = xsh_pfits_get_shiftifu_slitref( shift_header));

  check( xsh_pfits_set_shiftifu_lambdaref( header, waveref));
  check( xsh_pfits_set_shiftifu_slitref( header, slitref));

  cleanup:
    xsh_free_propertylist( &shift_header);
    return;
}
