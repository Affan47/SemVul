julia_trampoline(int argc, char *argv[], int (*pmain)(int ac,char *av[]))
{
#ifdef COPY_STACKS

    jl_root_task->stackbase = (char*)&argc;
    if (setjmp(jl_root_task->base_ctx)) {
        jl_switch_stack(jl_current_task, jl_jmp_target);
    }
#endif
    return pmain(argc, argv);
}
