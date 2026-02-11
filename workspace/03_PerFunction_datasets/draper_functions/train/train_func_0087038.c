unloadDll(DllEntry *dll, int unloader) {
    void *on_unload = nativeLibSym(dll->handle, "JNI_OnUnload");

    if(unloader || on_unload == NULL) {
        TRACE("<DLL: Unloading DLL %s\n", dll->name);

        if(on_unload != NULL) {
            initJNILrefs();
            (*(void (*)(JavaVM*, void*))on_unload)(&jni_invoke_intf, NULL);
        }

        nativeLibClose(dll->handle);
        sysFree(dll->name);
        sysFree(dll);
    }
}
