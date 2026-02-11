_coroutine_release(struct continuation *cc)
{
    struct coroutine *co = container_of(cc, struct coroutine, cc);

    if (co->release) {
        int ret = co->release(co);
        if (ret < 0)
            return ret;
    }

    munmap(co->cc.stack, co->cc.stack_size);

    co->caller = NULL;

    return 0;
}
