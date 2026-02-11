__Pyx_TraceSetupAndCall(PyCodeObject** code,
                                   PyFrameObject** frame,
                                   const char *funcname,
                                   const char *srcfile,
                                   int firstlineno) {
    if (*frame == NULL || !CYTHON_PROFILE_REUSE_FRAME) {
        if (*code == NULL) {
            *code = __Pyx_createFrameCodeObject(funcname, srcfile, firstlineno);
            if (*code == NULL) return 0;
        }
        *frame = PyFrame_New(
            PyThreadState_GET(),
            *code,
            PyModule_GetDict(__pyx_m),
            0
        );
        if (*frame == NULL) return 0;
    }
    else {
        (*frame)->f_tstate = PyThreadState_GET();
    }
    return PyThreadState_GET()->c_profilefunc(PyThreadState_GET()->c_profileobj, *frame, PyTrace_CALL, NULL) == 0;
}
