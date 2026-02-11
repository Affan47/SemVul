check_get_samdata(void)
{
  struct accountdb_F *f;
  struct keyval *v;

  if (H_SAM >= 0) {


    v = get_val2buf(hive[H_SAM], NULL, 0, ACCOUNTDB_F_PATH, REG_BINARY, TPF_VK);
    if (!v) {
      printf("Login counts data not found in SAM\n");
      return;
    }
    printf("\n* SAM policy limits:\n");

    f = (struct accountdb_F *)&v->data;
    max_sam_lock = f->locklimit;

    printf("Failed logins before lockout is: %d\n",max_sam_lock);
    printf("Minimum password length        : %d\n",f->minpwlen);
    printf("Password history count         : %d\n",f->minpwlen);

  }
}
