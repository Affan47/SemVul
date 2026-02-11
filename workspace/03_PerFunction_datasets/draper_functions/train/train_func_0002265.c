cbf_make_positioner (cbf_positioner *positioner)
{
  cbf_failnez (cbf_alloc ((void **) positioner, NULL,
               sizeof (cbf_positioner_struct), 1))

  (*positioner)->matrix [0][0] = 1;
  (*positioner)->matrix [0][1] = 0;
  (*positioner)->matrix [0][2] = 0;
  (*positioner)->matrix [0][3] = 0;
  (*positioner)->matrix [1][0] = 0;
  (*positioner)->matrix [1][1] = 1;
  (*positioner)->matrix [1][2] = 0;
  (*positioner)->matrix [1][3] = 0;
  (*positioner)->matrix [2][0] = 0;
  (*positioner)->matrix [2][1] = 0;
  (*positioner)->matrix [2][2] = 1;
  (*positioner)->matrix [2][3] = 0;

  (*positioner)->axis = NULL;

  (*positioner)->axes = 0;

  (*positioner)->matrix_is_valid = 1;

  (*positioner)->axes_are_connected = 1;

  return 0;
}
