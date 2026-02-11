Create_subarray(int ndims, const int array_of_sizes[],
		     const int array_of_subsizes[],
		     const int array_of_starts[], int order) const
{
  return pmpi_datatype.Create_subarray(ndims, array_of_sizes,
				       array_of_subsizes,
				       array_of_starts, order);
}
