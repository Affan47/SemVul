amdmsFreeData(amdmsDATA *data)
{
  if (data == NULL) {
    return amdmsFAILURE;
  }
  data->nx = 0;
  data->ny = 0;
  data->index = 0.0;
  if (data->data != NULL) {
    free(data->data);
    data->data = NULL;
  }
  return amdmsSUCCESS;
}
