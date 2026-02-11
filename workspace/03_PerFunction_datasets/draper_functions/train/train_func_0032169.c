prng_should_return_same_series_from_same_seeds() {
    theft_seed seeds[8];
    theft_seed values[8][8];

    theft *t = theft_init(0);


    theft_set_seed(t, 0xabad5eed);
    for (int i = 0; i < 8; i++) {
        seeds[i] = theft_random(t);
    }


    for (int s = 0; s < 8; s++) {
        theft_set_seed(t, seeds[s]);
        for (int i = 0; i < 8; i++) {
            values[s][i] = theft_random(t);
        }
    }


    for (int s = 0; s < 8; s++) {
        theft_set_seed(t, seeds[s]);
        for (int i = 0; i < 8; i++) {
            ASSERT_EQ(values[s][i], theft_random(t));
        }
    }
    theft_free(t);
    PASS();
}
