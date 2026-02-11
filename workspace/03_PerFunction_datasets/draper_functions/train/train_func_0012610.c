cogl_vector3_equal (const void *v1, const void *v2)
{
  float *vector0 = (float *)v1;
  float *vector1 = (float *)v2;

  _COGL_RETURN_VAL_IF_FAIL (v1 != NULL, FALSE);
  _COGL_RETURN_VAL_IF_FAIL (v2 != NULL, FALSE);


  return
    vector0[X] == vector1[X] &&
    vector0[Y] == vector1[Y] &&
    vector0[Z] == vector1[Z];
}
