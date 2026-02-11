do_flashall(int erase_first)
{
    char *fname;
    void *data;
    unsigned sz;

    queue_info_dump();

    fb_queue_query_save("product", cur_product, sizeof(cur_product));

    fname = find_item("info", product);
    if (fname == 0) die("cannot find android-info.txt");
    data = load_file(fname, &sz);
    if (data == 0) die("could not load android-info.txt: %s", strerror(errno));
    setup_requirements(data, sz);

    fname = find_item("boot", product);
    data = load_file(fname, &sz);
    if (data == 0) die("could not load boot.img: %s", strerror(errno));
    do_send_signature(fname);
    if (erase_first && needs_erase("boot")) {
        fb_queue_erase("boot");
    }
    fb_queue_flash("boot", data, sz);

    fname = find_item("recovery", product);
    data = load_file(fname, &sz);
    if (data != 0) {
        do_send_signature(fname);
        if (erase_first && needs_erase("recovery")) {
            fb_queue_erase("recovery");
        }
        fb_queue_flash("recovery", data, sz);
    }

    fname = find_item("system", product);
    data = load_file(fname, &sz);
    if (data == 0) die("could not load system.img: %s", strerror(errno));
    do_send_signature(fname);
    if (erase_first && needs_erase("system")) {
        fb_queue_erase("system");
    }
    fb_queue_flash("system", data, sz);
}
