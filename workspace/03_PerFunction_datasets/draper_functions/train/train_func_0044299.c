update_variable_lengths(int var_count, int* var_sizes)
{
  if (nofVariableValues == 0)
    return true;

  int old_nof_values = nofVariableValues - var_count;

  int* var_lengths = new int[nofVariableValues];

  int i;

  for (i = 0; i < old_nof_values; i++)
    var_lengths[i] = variableLengths[i];

  for (i = 0; i < var_count; i++)
    var_lengths[old_nof_values + i] = var_sizes[i];

  delete[] variableLengths;

  variableLengths = var_lengths;

  return true;
}
