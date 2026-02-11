generated_unsigned_ints_are_positive() {
    theft *t = theft_init(0);

    theft_run_res res;


    res = theft_run(t, &(struct theft_cfg){
            .name = "generated_unsigned_ints_are_positive",
            .fun = is_pos,
            .type_info = { &uint },
            .progress_cb = guiap_prog_cb,
        });
    ASSERT_EQm("generated_unsigned_ints_are_positive", THEFT_RUN_PASS, res);
    theft_free(t);
    PASS();
}
