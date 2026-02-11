getfssec(com32sys_t *regs)
{
    int sectors;
    bool have_more;
    uint32_t bytes_read;
    char *buf;
    struct file *file;
    uint16_t handle;

    sectors = regs->ecx.w[0];

    handle = regs->esi.w[0];
    file = handle_to_file(handle);

    buf = MK_PTR(regs->es, regs->ebx.w[0]);
    bytes_read = file->fs->fs_ops->getfssec(file, buf, sectors, &have_more);


    if (!have_more) {
	_close_file(file);
        regs->esi.w[0] = 0;
    }

    regs->ecx.l = bytes_read;
}
