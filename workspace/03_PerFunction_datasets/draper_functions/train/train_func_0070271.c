printprocess(struct process_control_block process) {
    int i = 0;

    printf("pid: %d ", process.pid);
    printf("psw: %d ", process.psw);
    printf("p_table: %d ", process.page_table);
    printf("regs:");
    for (i = 0; i < NUM_REGS; i++) {
   	printf(" %d ", process.regs[i]);
    }
    printf("\n");
}
