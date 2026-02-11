get_lr_shift(int mode)
{

  const int *ptr_lr_shift;


  if((mode & COLOR_MODE_K) == (mode & COLOR_MODE_MASK)) {
    ptr_lr_shift = lr_shift_black;
  } else {
    ptr_lr_shift = lr_shift_color;
  }

      switch(mode & PRINT_MODE_MASK) 	{
	case PRINT_MODE_300:
	  return ptr_lr_shift[0];
	  break;
	case PRINT_MODE_600:
	  return ptr_lr_shift[1];
	  break;
	case PRINT_MODE_1200:
	  return ptr_lr_shift[2];
	  break;
	case PRINT_MODE_2400:
	  return ptr_lr_shift[2];
	  break;
      }
      return 0;
}
