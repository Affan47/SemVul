send_shellcommand(transport_type transport, char* serial, char* buf)
{
    int fd, ret;

    for(;;) {
        fd = adb_connect(buf);
        if(fd >= 0)
            break;
        fprintf(stderr,"- waiting for device -\n");
        adb_sleep_ms(1000);
        do_cmd(transport, serial, "wait-for-device", 0);
    }

    read_and_dump(fd);
    ret = adb_close(fd);
    if (ret)
        perror("close");

    return ret;
}
