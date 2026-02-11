stage_data_shift_test(const stage_data& sd,
                      const int stage_id,
                      const unsigned expect) {

    const unsigned result(sd.get_stage_id_shift(stage_id));
    BOOST_CHECK_EQUAL(result,expect);
}
