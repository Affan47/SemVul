run_ecmult_gen_blind(void) {
    int i;
    test_ecmult_gen_blind_reset();
    for (i = 0; i < 10; i++) {
        test_ecmult_gen_blind();
    }
}
