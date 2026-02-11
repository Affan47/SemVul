__pyx_f_7dumbnet_ip_checksum(PyObject *__pyx_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  PyObject *__pyx_v_pkt = 0;
  char __pyx_v_buf[2048];
  char *__pyx_v_p;
  int __pyx_v_n;
  PyObject *__pyx_v_s;
  PyObject *__pyx_r;
  int __pyx_1;
  PyObject *__pyx_2 = 0;
  char *__pyx_3;
  static char *__pyx_argnames[] = {"pkt",0};
  if (!PyArg_ParseTupleAndKeywords(__pyx_args, __pyx_kwds, "O", __pyx_argnames, &__pyx_v_pkt)) return 0;
  Py_INCREF(__pyx_v_pkt);
  __pyx_v_s = Py_None; Py_INCREF(Py_None);


  __pyx_1 = (PyObject_AsReadBuffer(__pyx_v_pkt,(&__pyx_v_p),(&__pyx_v_n)) == 0);
  if (__pyx_1) {


    __pyx_1 = (__pyx_v_n < 2048);
    if (__pyx_1) {


      memcpy(__pyx_v_buf,__pyx_v_p,__pyx_v_n);


      ip_checksum(__pyx_v_buf,__pyx_v_n);


      __pyx_2 = PyString_FromStringAndSize(__pyx_v_buf,__pyx_v_n); if (!__pyx_2) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 300; goto __pyx_L1;}
      __pyx_r = __pyx_2;
      __pyx_2 = 0;
      goto __pyx_L0;
      goto __pyx_L3;
    }
    __pyx_L3:;


    __pyx_v_p = malloc(__pyx_v_n);


    __pyx_3 = PyString_AsString(__pyx_v_pkt); if (!__pyx_3) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 302; goto __pyx_L1;}
    memcpy(__pyx_v_p,__pyx_3,__pyx_v_n);


    ip_checksum(__pyx_v_p,__pyx_v_n);


    __pyx_2 = PyString_FromStringAndSize(__pyx_v_p,__pyx_v_n); if (!__pyx_2) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 304; goto __pyx_L1;}
    Py_DECREF(__pyx_v_s);
    __pyx_v_s = __pyx_2;
    __pyx_2 = 0;


    free(__pyx_v_p);


    Py_INCREF(__pyx_v_s);
    __pyx_r = __pyx_v_s;
    goto __pyx_L0;
    goto __pyx_L2;
  }
  __pyx_L2:;


  __Pyx_Raise(PyExc_TypeError, 0, 0);
  {__pyx_filename = __pyx_f[0]; __pyx_lineno = 307; goto __pyx_L1;}

  __pyx_r = Py_None; Py_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1:;
  Py_XDECREF(__pyx_2);
  __Pyx_AddTraceback("dumbnet.ip_checksum");
  __pyx_r = 0;
  __pyx_L0:;
  Py_DECREF(__pyx_v_s);
  Py_DECREF(__pyx_v_pkt);
  return __pyx_r;
}
