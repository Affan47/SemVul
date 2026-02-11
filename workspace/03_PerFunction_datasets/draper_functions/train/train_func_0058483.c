ntru_tern_to_arr(NtruTernPoly *poly, uint8_t *arr) {
    uint8_t *arr_head = arr;


    uint16_t num_ones = htons(poly->num_ones);
    memcpy(arr_head, &num_ones, sizeof num_ones);
    arr_head += sizeof num_ones;
    uint16_t num_neg_ones = htons(poly->num_neg_ones);
    memcpy(arr_head, &num_neg_ones, sizeof num_neg_ones);
    arr_head += sizeof num_neg_ones;


    uint16_t i;
    for (i=0; i<poly->num_ones; i++) {
        uint16_t idx = htons(poly->ones[i]);
        memcpy(arr_head, &idx, sizeof idx);
        arr_head += sizeof idx;
    }
    for (i=0; i<poly->num_neg_ones; i++) {
        uint16_t idx = htons(poly->neg_ones[i]);
        memcpy(arr_head, &idx, sizeof idx);
        arr_head += sizeof idx;
    }

    return arr_head - arr;
}
