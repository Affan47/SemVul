bpred_dir_create (
  enum bpred_class class,
  unsigned int l1size,
  unsigned int l2size,
  unsigned int shift_width,
  unsigned int xor)
{
  struct bpred_dir_t *pred_dir;
  unsigned int cnt;
  int flipflop;

  if (!(pred_dir = calloc(1, sizeof(struct bpred_dir_t))))
    fatal("out of virtual memory");

  pred_dir->class = class;

  cnt = -1;
  switch (class) {
  case BPred2Level:
    {
      if (!l1size || (l1size & (l1size-1)) != 0)
	fatal("level-1 size, `%d', must be non-zero and a power of two",
	      l1size);
      pred_dir->config.two.l1size = l1size;

      if (!l2size || (l2size & (l2size-1)) != 0)
	fatal("level-2 size, `%d', must be non-zero and a power of two",
	      l2size);
      pred_dir->config.two.l2size = l2size;

      if (!shift_width || shift_width > 30)
	fatal("shift register width, `%d', must be non-zero and positive",
	      shift_width);
      pred_dir->config.two.shift_width = shift_width;

      pred_dir->config.two.xor = xor;
      pred_dir->config.two.shiftregs = calloc(l1size, sizeof(int));
      if (!pred_dir->config.two.shiftregs)
	fatal("cannot allocate shift register table");

      pred_dir->config.two.l2table = calloc(l2size, sizeof(unsigned char));
      if (!pred_dir->config.two.l2table)
	fatal("cannot allocate second level table");


      flipflop = 1;
      for (cnt = 0; cnt < l2size; cnt++)
	{
	  pred_dir->config.two.l2table[cnt] = flipflop;
	  flipflop = 3 - flipflop;
	}

      break;
    }

  case BPred2bit:
    if (!l1size || (l1size & (l1size-1)) != 0)
      fatal("2bit table size, `%d', must be non-zero and a power of two",
	    l1size);
    pred_dir->config.bimod.size = l1size;
    if (!(pred_dir->config.bimod.table =
	  calloc(l1size, sizeof(unsigned char))))
      fatal("cannot allocate 2bit storage");

    flipflop = 1;
    for (cnt = 0; cnt < l1size; cnt++)
      {
	pred_dir->config.bimod.table[cnt] = flipflop;
	flipflop = 3 - flipflop;
      }

    break;

  case BPredTaken:
  case BPredNotTaken:

    break;

  default:
    panic("bogus branch direction predictor class");
  }

  return pred_dir;
}
