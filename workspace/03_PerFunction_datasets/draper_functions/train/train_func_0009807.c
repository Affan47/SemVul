fork (void)
{
    struct page_directory_t *directory;
    struct task_t *parent_task;
    struct task_t *new_task;
    struct task_t *tmp_task;
    uint32_t eip;

    cli ();

    parent_task = (struct task_t *) current_task;
    directory = clone_directory (current_directory);


    new_task = (struct task_t *) kmalloc (sizeof (struct task_t));
    new_task->id = next_pid++;
    new_task->esp = new_task->ebp = 0;
    new_task->eip = 0;
    new_task->page_directory = directory;
    current_task->kernel_stack = kmalloc_a (KERNEL_STACK_SIZE);
    new_task->next = 0;


    tmp_task = (struct task_t *) ready_queue;
    while (tmp_task->next)
        tmp_task = tmp_task->next;
    tmp_task->next = new_task;

    eip = read_eip ();


    if (current_task == parent_task)
    {
        uint32_t esp, ebp;

        asm volatile ("mov %%esp, %0" : "=r"(esp));
        asm volatile ("mov %%ebp, %0" : "=r"(ebp));

        new_task->esp = esp;
        new_task->ebp = ebp;
        new_task->eip = eip;

        sti ();
        return new_task->id;
    }
    else
    {
        return 0;
    }
}
