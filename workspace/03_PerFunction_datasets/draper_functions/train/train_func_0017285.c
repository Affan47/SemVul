main(int argc, char *argv[])
{
    libsupport_init();
    parse_opts(&argc, &argv);
    julia_init(lisp_prompt ? NULL : image_file);
    return julia_trampoline(argc, argv, true_main);
}
