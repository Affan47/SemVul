free_data_refs (VEC (data_reference_p, heap) *datarefs)
{
  unsigned int i;
  struct data_reference *dr;

  FOR_EACH_VEC_ELT (data_reference_p, datarefs, i, dr)
    free_data_ref (dr);
  VEC_free (data_reference_p, heap, datarefs);
}
