__init_acc(void)
{
 register int32 aii;

 __acc_open = FALSE;
 acc_error_flag = FALSE;
 __acc_scope_set = FALSE;
 __acc_scope_vpiobj = NULL;
 __aiter_freelst = NULL;


 if (__acc_strbuf == NULL) __acc_strbuf = __my_malloc(ACCSTRBUFSIZ);
 __acc_strbuf_nxti = 0;


 __aiter_tab = (struct acciter_t **)
  __my_malloc((TOPVPIVAL + 1)*(sizeof(struct acciter_t *)));
 for (aii = 0; aii <= TOPVPIVAL; aii++) __aiter_tab[aii] = NULL;
 __last_aiter = NULL;
 __aiter_accnxt_list = NULL;

 __aithtsiz = 0;
 __aithtab = NULL;
 __aithrectab = NULL;
 __aithtsiz2 = 0;
 __aithtab2 = NULL;
 __aithrectab2 = NULL;


 init_acc_config();
}
