serial_float(t_serial *x, t_float f)
{
    int n = f;
    char message[MAXSERIAL * 4 + 100];
    if (!x->x_open)
    {
        sys_vgui("com%d_open\n", x->x_portno);
        x->x_open = 1;
    }
    sprintf(message, "com%d_send \"\\%3.3o\"\n", x->x_portno, n);
    sys_gui(message);
}
