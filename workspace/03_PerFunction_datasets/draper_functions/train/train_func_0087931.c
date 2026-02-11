peak_for (bin64_t pos) const {
    int pi=0;
    while (pi<peak_count_ && !pos.within(peaks_[pi]))
        pi++;
    return pi==peak_count_ ? bin64_t(bin64_t::NONE) : peaks_[pi];
}
