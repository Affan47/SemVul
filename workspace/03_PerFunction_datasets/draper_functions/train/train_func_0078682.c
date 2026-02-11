write_somatic_indel_vcf_grid(const somatic_indel_call& sindel,
                             const starling_indel_report_info& iri,
                             const starling_indel_sample_report_info* nisri,
                             const starling_indel_sample_report_info* tisri,
                             std::ostream& os) {

    const somatic_indel_call::result_set& rs(sindel.rs);

    os << '\t' << iri.vcf_ref_seq
       << '\t' << iri.vcf_indel_seq
       << '\t' << '.'
       << '\t' << '.';


    os << '\t'
       << "SOMATIC"
       << ";QSI=" << rs.sindel_qphred
       << ";TQSI=" << (sindel.sindel_tier+1)
       << ";NT=" << NTYPE::label(rs.ntype)
       << ";QSI_NT=" << rs.sindel_from_ntype_qphred
       << ";TQSI_NT=" << (sindel.sindel_from_ntype_tier+1)
       << ";SGT=" << static_cast<DDIINDEL_GRID::index_t>(rs.max_gt);
    if (iri.repeat_unit != "N/A") {
        os << ";RU=" << iri.repeat_unit
           << ";RC=" << iri.ref_repeat_count
           << ";IC=" << iri.indel_repeat_count;
    }
    os << ";IHP=" << iri.ihpol;
    if ((iri.it == INDEL::BP_LEFT) ||
        (iri.it == INDEL::BP_RIGHT)) {
        os << ";SVTYPE=BND";
    }
    if (rs.is_overlap) {
        os << ";OVERLAP";
    }


    os << '\t' << "DP:DP2:TAR:TIR:TOR";


    os << '\t';
    write_vcf_isri_tiers(nisri[0],nisri[1],os);


    os << '\t';
    write_vcf_isri_tiers(tisri[0],tisri[1],os);

}
