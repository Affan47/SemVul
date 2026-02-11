merge_bubbles(struct state *st, Bubble *b1, Bubble *b2)


{
  int b1size, b2size;

  b1size = b1->area;
  b2size = b2->area;

#ifdef DEBUG
  if ((null_bubble(b1) || null_bubble(b2))) {
    fprintf(stderr, "NULL bubble passed to merge_bubbles()!\n");
    exit(1);
  }
#endif

  if (b1 == b2) {
    hide_bubble(st, b1);
    delete_bubble_in_mesh(st, b1, DELETE_BUBBLE);
    return 0;
  }

  if (b1size > b2size) {
    switch (bubble_eat(st, b1, b2)) {
    case 0:
      return 0;
      break;
    case 1:
      return 1;
      break;
    default:
      break;
    }
  } else if (b1size < b2size) {
    switch (bubble_eat(st, b2, b1)) {
    case 0:
      return 0;
      break;
    case 1:
      return 2;
      break;
    default:
      break;
    }
  } else {
    if ((random() % 2) == 0) {
      switch (bubble_eat(st, b1, b2)) {
      case 0:
	return 0;
	break;
      case 1:
	return 1;
	break;
      default:
	break;
      }
    } else {
      switch (bubble_eat(st, b2, b1)) {
      case 0:
	return 0;
	break;
      case 1:
	return 2;
	break;
      default:
	break;
      }
    }
  }
  fprintf(stderr, "An error occurred in merge_bubbles()\n");
  exit(1);
}
