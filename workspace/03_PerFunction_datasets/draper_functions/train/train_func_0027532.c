get_regs_stack_item(int n) {
    while (n >= regs_stack_max) {
        int max = regs_stack_max;
        regs_stack_max = regs_stack_max == 0 ? 8 : regs_stack_max * 2;
        regs_stack = (StackFrameRegisters *)loc_realloc(regs_stack, sizeof(StackFrameRegisters) * regs_stack_max);
        memset(regs_stack + max, 0, sizeof(StackFrameRegisters) * (regs_stack_max - max));
    }
    return regs_stack + n;
}
