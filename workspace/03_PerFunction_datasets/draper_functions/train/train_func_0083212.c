ac_data_values_destroy (gcry_ac_data_t data)
{
  unsigned int i;

  for (i = 0; i < data->data_n; i++)
    if (data->data[i].flags & GCRY_AC_FLAG_DEALLOC)
      {
	gcry_mpi_release (data->data[i].mpi);
	gcry_free (data->data[i].name);
      }
}
