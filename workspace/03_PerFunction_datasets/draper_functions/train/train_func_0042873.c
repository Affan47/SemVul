main(void)
{
    pthread_attr_t attribute;
    int ret;

    pthread_attr_init(&attribute);
    ret=pthread_attr_setscope(&attribute, PTHREAD_SCOPE_SYSTEM);
    if (ret==0)
        return 0;
    return 1;
}
