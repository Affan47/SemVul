rb_dlhandle_initialize(int argc, VALUE argv[], VALUE self)
{
    void *ptr;
    struct dl_handle *dlhandle;
    VALUE lib, flag;
    char  *clib;
    int   cflag;
    const char *err;

    switch( rb_scan_args(argc, argv, "02", &lib, &flag) ){
      case 0:
	clib = NULL;
	cflag = RTLD_LAZY | RTLD_GLOBAL;
	break;
      case 1:
	clib = NIL_P(lib) ? NULL : StringValuePtr(lib);
	cflag = RTLD_LAZY | RTLD_GLOBAL;
	break;
      case 2:
	clib = NIL_P(lib) ? NULL : StringValuePtr(lib);
	cflag = NUM2INT(flag);
	break;
      default:
	rb_bug("rb_dlhandle_new");
    }

    rb_secure(2);

#if defined(_WIN32)
    if( !clib ){
	HANDLE rb_libruby_handle(void);
	ptr = rb_libruby_handle();
    }
    else if( STRCASECMP(clib, "libc") == 0
# ifdef RUBY_COREDLL
	     || STRCASECMP(clib, RUBY_COREDLL) == 0
	     || STRCASECMP(clib, RUBY_COREDLL".dll") == 0
# endif
	){
# ifdef _WIN32_WCE
	ptr = dlopen("coredll.dll", cflag);
# else
	ptr = w32_coredll();
# endif
    }
    else
#endif
	ptr = dlopen(clib, cflag);
#if defined(HAVE_DLERROR)
    if( !ptr && (err = dlerror()) ){
	rb_raise(rb_eDLError, "%s", err);
    }
#else
    if( !ptr ){
	err = dlerror();
	rb_raise(rb_eDLError, "%s", err);
    }
#endif
    TypedData_Get_Struct(self, struct dl_handle, &dlhandle_data_type, dlhandle);
    if( dlhandle->ptr && dlhandle->open && dlhandle->enable_close ){
	dlclose(dlhandle->ptr);
    }
    dlhandle->ptr = ptr;
    dlhandle->open = 1;
    dlhandle->enable_close = 0;

    if( rb_block_given_p() ){
	rb_ensure(rb_yield, self, rb_dlhandle_close, self);
    }

    return Qnil;
}
