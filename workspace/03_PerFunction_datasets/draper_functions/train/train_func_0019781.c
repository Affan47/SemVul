pushJNILrefFrame(int cap) {
    ExecEnv *ee = getExecEnv();
    JNIFrame *frame = (JNIFrame*)ee->last_frame;
    JNIFrame *new_frame = (JNIFrame*)((Object**)(frame + 1) + cap);

    if((char*)(new_frame + 1) > ee->stack_end) {
        signalException(java_lang_OutOfMemoryError, "JNI local references");
        return NULL;
    }

    new_frame->lrefs = new_frame->next_ref = (Object**)(frame + 1);
    new_frame->ostack = (uintptr_t*)(new_frame + 1);
    new_frame->prev = frame->prev;
    new_frame->mb = frame->mb;

    memset(frame + 1, 0, cap * sizeof(Object*));
    ee->last_frame = (Frame*)new_frame;

    return new_frame;
}
