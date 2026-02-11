f_telnet_recv(int cmd, int opt)
{
    if (telopt) {
        char buf[4];
        sprintf(buf, "%c%c%c", TN_IAC, cmd, opt);
        telnet_debug("recv", buf,
            (cmd==(UCHAR)TN_DO || cmd==(UCHAR)TN_DONT ||
             cmd==(UCHAR)TN_WILL || cmd==(UCHAR)TN_WONT) ?
             3 : 2);
    }
}
