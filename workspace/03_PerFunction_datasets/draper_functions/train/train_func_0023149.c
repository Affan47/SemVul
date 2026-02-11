gregorio_det_step_and_line_from_key (int key, char *step, int *line)
{
  switch (key)
    {
    case -2:
      *step = 'f';
      *line = 1;
      break;
    case 0:
      *step = 'f';
      *line = 2;
      break;
    case 2:
      *step = 'f';
      *line = 3;
      break;
    case 4:
      *step = 'f';
      *line = 4;
      break;
    case 1:
      *step = 'c';
      *line = 1;
      break;
    case 3:
      *step = 'c';
      *line = 2;
      break;
    case 5:
      *step = 'c';
      *line = 3;
      break;
    case 7:
      *step = 'c';
      *line = 4;
      break;
    default:
      *step = '?';
      *line = 0;
      gregorio_message (_("can't determine step and line of the key"),
			   "gregorio_det_step_and_line_from_key", ERROR,
			   0);
      return;
    }
}
