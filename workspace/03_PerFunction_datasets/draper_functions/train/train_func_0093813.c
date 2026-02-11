shutdown(JNIEnv *env, jobject source, jboolean reload)
{
    log_debug("Shutdown requested (reload is %d)", reload);
    if (reload == TRUE)
        main_reload();
    else
        main_shutdown();
}
