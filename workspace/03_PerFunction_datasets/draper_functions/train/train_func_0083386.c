do_local_optimize() {
    const char* NAMES[] = { "[(nothing)]" };
    const int COUNT = sizeof(NAMES) / sizeof(const char*);

    bool is_okay = true;

    for (int i = 0; i < COUNT; i++) {
        gm_begin_minor_compiler_stage(i + 1, NAMES[i]);
        {
            switch (i) {
                case 0:
                    break;
                case COUNT:
                default:
                    assert(false);
                    break;
            }
        }
        gm_end_minor_compiler_stage();
        if (!is_okay) break;
    }
    return is_okay;
}
