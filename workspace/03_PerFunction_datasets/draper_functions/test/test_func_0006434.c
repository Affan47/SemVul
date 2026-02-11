chk_succ(ret_flag, susp_stor)
int ret_flag;
struct store *susp_stor;
   {
   if (ret_flag & DoesSusp) {
       if (susp_stor != NULL && (ret_flag & DoesRet))
          mrg_store(susp_stor, fail_store);
       fail_store = susp_stor;
       }
   else if (!(ret_flag & DoesRet)) {
      free_store(succ_store);
      succ_store = get_store(1);
      fail_store = dummy_stor;
      }
   }
