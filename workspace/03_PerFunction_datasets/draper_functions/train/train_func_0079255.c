get_align_score(const hap_cand& hc,
                const hinfo& hi) {


    static const double ln_one_third(-std::log(3.0));

    double score(0);
    for (unsigned i(0); i<hap_cand::HAP_SIZE; ++i) {
        if ((hi.hseq[i] == BASE_ID::ANY) ||
            (hc.base_id(i) == BASE_ID::ANY)) {

        } else if (hi.hseq[i] != hc.base_id(i)) {
            score += qphred_to_ln_error_prob(hc.qual(i)) + ln_one_third - qphred_to_ln_comp_error_prob(hc.qual(i));
        }
    }

    return score;
}
