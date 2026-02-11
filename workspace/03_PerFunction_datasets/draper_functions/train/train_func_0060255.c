utimes (const char *pathname, const struct timeval *newtimes) {
       int result;
       instw_t instw;

       if (!libc_handle)
               initialize();

#if DEBUG
       debug(2,"utimes(%s,newtimes)\n",pathname);
#endif


       if( !(__instw.gstatus & INSTW_INITIALIZED) ||
           !(__instw.gstatus & INSTW_OKWRAP) ) {
               result=true_utimes(pathname,newtimes);
               return result;
       }

       instw_new(&instw);
       instw_setpath(&instw,pathname);

#if DEBUG
       instw_print(&instw);
#endif

       backup(instw.truepath);
       instw_apply(&instw);

       result=true_utimes(instw.translpath,newtimes);
       logg("%d\tutimes\t%s\t#%s\n",result,instw.reslvpath,error(result));

       instw_delete(&instw);

       return result;
}
