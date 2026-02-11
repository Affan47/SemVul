usbtiny_avr_op (PROGRAMMER * pgm, AVRPART * p,
			   int op,
			   unsigned char *res)
{
  unsigned char	cmd[4];

  if (p->op[op] == NULL) {
    fprintf( stderr, "Operation %d not defined for this chip!\n", op );
    return -1;
  }
  memset(cmd, 0, sizeof(cmd));
  avr_set_bits(p->op[op], cmd);

  return pgm->cmd(pgm, cmd, res);
}
