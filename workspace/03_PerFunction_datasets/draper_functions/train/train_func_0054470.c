classlibInitJavaThread(Thread *thread, Object *jlthread, Object *name,
                            Object *group, char is_daemon, int priority) {

    INST_DATA(jlthread, Thread*, eetop_offset) = thread;
    INST_DATA(jlthread, int, daemon_offset) = is_daemon;
    INST_DATA(jlthread, int, priority_offset) = priority;

    if(name == NULL)
        executeMethod(jlthread, init_mb_no_name, group, NULL);
    else
        executeMethod(jlthread, init_mb_with_name, group, name);

    return !exceptionOccurred();
}
