setExtendedStrut(const NETExtendedStrut &extended_strut)
{
    if (role != Client) return;
    p->extended_strut = extended_strut;
    long data[12];
    data[0] = extended_strut.left_width;
    data[1] = extended_strut.right_width;
    data[2] = extended_strut.top_width;
    data[3] = extended_strut.bottom_width;
    data[4] = extended_strut.left_start;
    data[5] = extended_strut.left_end;
    data[6] = extended_strut.right_start;
    data[7] = extended_strut.right_end;
    data[8] = extended_strut.top_start;
    data[9] = extended_strut.top_end;
    data[10] = extended_strut.bottom_start;
    data[11] = extended_strut.bottom_end;
    XChangeProperty(p->display, p->window, net_wm_extended_strut, XA_CARDINAL, 32,
     PropModeReplace, (unsigned char *) data, 12);
}
