set_string(struct condition *cond, struct res_db *db,
	   struct input *in, anthy_context_t ac)
{
  struct conv_res *cr1, *cr2;
  int pr;

  anthy_set_string(ac, in->str);


  cr1 = find_conv_res(db, ac, in->str, 1);
  sum_up(db, cr1);

  cr2 = find_conv_res(db, ac, in->str, 0);
  sum_up(db, cr2);


  pr = 0;
  if (cond->miss_only) {
    if (cr1->check == CHK_MISS ||
	cr2->check == CHK_MISS) {
      pr = 1;
    }
  } else if (!cond->quiet) {
    pr = 1;
  }

  if (pr) {
    printf("%d:(%s)\n", in->serial, in->str);
    anthy_print_context(ac);
  }
  anthy_reset_context(ac);
}
