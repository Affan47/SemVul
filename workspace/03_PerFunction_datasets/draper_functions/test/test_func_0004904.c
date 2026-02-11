set_vm_env(JNIEnv *vm_env)
{
    if (!VM_ENV)
        pthread_key_create(&VM_ENV, NULL);
    pthread_setspecific(VM_ENV, (void *) vm_env);
}
