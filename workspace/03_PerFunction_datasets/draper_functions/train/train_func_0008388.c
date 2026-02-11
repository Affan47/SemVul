do_send_signature(char *fn)
{
    void *data;
    unsigned sz;
    char *xtn;

    xtn = strrchr(fn, '.');
    if (!xtn) return;
    if (strcmp(xtn, ".img")) return;

    strcpy(xtn,".sig");
    data = load_file(fn, &sz);
    strcpy(xtn,".img");
    if (data == 0) return;
    fb_queue_download("signature", data, sz);
    fb_queue_command("signature", "installing signature");
}
