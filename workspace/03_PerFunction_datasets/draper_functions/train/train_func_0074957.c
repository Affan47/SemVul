alignedFree(void* _ptr) {
    if (_ptr == NULL) {
        return;
    }

    size_t alignedPtr = (size_t)_ptr;


    size_t* redirectPtr = (size_t*)(alignedPtr - sizeof(void *));


    void* truePtr = (void*)redirectPtr[0];

    debugAssert(isValidHeapPointer((void*)truePtr));
    System::free(truePtr);
}
