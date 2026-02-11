get_map_level(const starling_options& opt,
              const bam_record& read) {

    using namespace MAPLEVEL;

    if (read.is_unmapped()) return UNMAPPED;

    if (is_usable_read_mapping(opt,read)) return TIER1_MAPPED;
    if (opt.is_tier2()) {
        if (is_usable_read_mapping(opt,read,true)) return TIER2_MAPPED;
    }
    return SUB_MAPPED;
}
