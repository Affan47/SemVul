do_strrchr(void) {
  char	*pnt, *val, *ret;
  char	*func_name = "rindex";

  pnt = malloc(5);
  val = "foot";
  strcpy(pnt, val);

  ret = strrchr(pnt, *val);
  if (! check_ok(func_name)) {
    return 0;
  }

  if (ret != pnt) {
    if (! silent_b) {
      (void)printf("   ERROR: %s should have found the f\n", func_name);
    }
    return 0;
  }

  val = "footy";
  memmove(pnt, val, strlen(val));
  strrchr(pnt, *val);
  return check_fail(func_name, ERROR_WOULD_OVERWRITE);
}
