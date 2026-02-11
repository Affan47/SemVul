make_jdata(int fd, const char *value)
{
        int err;
        uint32_t val;

        err = ioctl(fd, FS_IOC_GETFLAGS, &val);
        if (err){
		perror("GETFLAGS");
		exit(EXIT_FAILURE);
	}

        if (strcmp(value, "set") == 0)
                val |= FS_JOURNAL_DATA_FL;
        if (strcmp(value, "clear") == 0)
                val &= ~FS_JOURNAL_DATA_FL;
        err = ioctl(fd, FS_IOC_SETFLAGS, &val);

        if (err){
		perror("SETFLAGS");
		exit(EXIT_FAILURE);
	}
}
