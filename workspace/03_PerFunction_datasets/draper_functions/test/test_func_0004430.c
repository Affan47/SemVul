PopErrorHandler()
  {
     void* user_data = CPLGetErrorHandlerUserData();
     if( user_data != NULL )
       Py_XDECREF((PyObject*)user_data);
     CPLPopErrorHandler();
  }
