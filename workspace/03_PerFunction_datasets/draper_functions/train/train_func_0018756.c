set_msr_value (int cpu, uint32_t reg, uint64_t data)
{
    int fd;
    char msr_file_name[64];

    sprintf (msr_file_name, "/dev/cpu/%d/msr", cpu);
    fd = open (msr_file_name, O_WRONLY);
    if (fd < 0)
    {
        if (errno == ENXIO)
        {
            fprintf (stderr, "wrmsr: No CPU %d\n", cpu);
            exit (2);
        } else if (errno == EIO) {
            fprintf (stderr, "wrmsr: CPU %d doesn't support MSRs\n", cpu);
            exit (3);
        } else {
            perror ("wrmsr:open");
            exit (127);
        }
    }

    if (pwrite (fd, &data, sizeof data, reg) != sizeof data)
    {
        perror ("wrmsr:pwrite");
        exit (127);
    }
    close(fd);
    return(1);
}
