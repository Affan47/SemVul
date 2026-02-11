send_3x3_matrix (Avision_Scanner* s)
{
  SANE_Status status;

#define SIGN_BIT 0x1000
#define INT_PART 10

  struct matrix_cmd
  {
    struct command_send scmd;
    struct matrix_3x3 matrix;
  } cmd;


  int i, a_i;
  static const double c5_matrix[] =
    { 1.000, 0.000, 0.000,
      0.000, 1.000, 0.000,
      0.000, 0.000, 1.000 };

  double a_f, b_f;
  uint16_t m;

  DBG (3, "send_3x3_matrix:\n");

  memset (&cmd, 0, sizeof (cmd));

  for (i = 0; i < 9; i++)
    {
      m = 0;
      a_f = c5_matrix[i];
      if (a_f < 0) {
	m |= SIGN_BIT;
	a_f = -a_f;
      }

      a_i = (int) a_f;
      b_f = a_f - (double) a_i;
      m |= ((a_i & 0x3) << INT_PART);
      m |= (uint16_t) (b_f * 1024);
      set_double (((uint8_t*)(&cmd.matrix.v[i])), m);
    }

  cmd.scmd.opc = AVISION_SCSI_SEND;
  cmd.scmd.datatypecode = 0x83;
  set_triple (cmd.scmd.transferlen, sizeof (struct matrix_3x3));

  if (1) {
    DBG (3, "send_3x3_matrix: sending matrix split into two commands\n");
    status = avision_cmd (&s->av_con, &cmd.scmd, sizeof (cmd.scmd),
                          &cmd.matrix, sizeof(cmd.matrix), 0, 0);
  }
  else {
    DBG (3, "send_3x3_matrix: sending matrix in one command\n");
    status = avision_cmd (&s->av_con, &cmd, sizeof (cmd), 0, 0, 0, 0);
  }

  return status;
}
