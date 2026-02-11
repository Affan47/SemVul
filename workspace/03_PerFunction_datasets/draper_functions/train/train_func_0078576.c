finish_gvcf_header(const gvcf_options& opt,
                   const cdmap_t& chrom_depth,
                   const std::string& bam_header_data,
                   std::ostream& os) {


    os << "##INFO=<ID=END,Number=1,Type=Integer,Description=\"End position of the region described in this record\">\n";
    os << "##INFO=<ID=BLOCKAVG_min30p3a,Number=0,Type=Flag,Description=\"Non-variant site block. All sites in a block are constrained to be non-variant, have the same filter value, and have all sample values in range [x,y], y <= max(x+3,(x*1.3)). All printed site block sample values are the minimum observed in the region spanned by the block\">\n";


    os << "##INFO=<ID=SNVSB,Number=1,Type=Float,Description=\"SNV site strand bias\">\n";
    os << "##INFO=<ID=SNVHPOL,Number=1,Type=Integer,Description=\"SNV contextual homopolymer length\">\n";


    os << "##INFO=<ID=CIGAR,Number=A,Type=String,Description=\"CIGAR alignment for each alternate indel allele\">\n";
    os << "##INFO=<ID=RU,Number=A,Type=String,Description=\"Smallest repeating sequence unit extended or contracted in the indel allele relative to the reference. RUs are not reported if longer than 20 bases.\">\n";
    os << "##INFO=<ID=REFREP,Number=A,Type=Integer,Description=\"Number of times RU is repeated in reference.\">\n";
    os << "##INFO=<ID=IDREP,Number=A,Type=Integer,Description=\"Number of times RU is repeated in indel allele.\">\n";


    os << "##FORMAT=<ID=GT,Number=1,Type=String,Description=\"Genotype\">\n";
    os << "##FORMAT=<ID=GQ,Number=1,Type=Float,Description=\"Genotype Quality\">\n";
    os << "##FORMAT=<ID=GQX,Number=1,Type=Integer,Description=\"Minimum of {Genotype quality assuming variant position,Genotype quality assuming non-variant position}\">\n";
    os << "##FORMAT=<ID=DP,Number=1,Type=Integer,Description=\"Filtered basecall depth used for site genotyping\">\n";
    os << "##FORMAT=<ID=DPF,Number=1,Type=Integer,Description=\"Basecalls filtered from input prior to site genotyping\">\n";

    os << "##FORMAT=<ID=AD,Number=.,Type=Integer,Description=\"Allelic depths for the ref and alt alleles in the order listed. For indels this value only includes reads which confidently support each allele (posterior prob 0.999 or higher that read contains indicated allele vs all other intersecting indel alleles)\">\n";

    os << "##FORMAT=<ID=DPI,Number=1,Type=Integer,Description=\"Read depth associated with indel, taken from the site preceding the indel.\">\n";


    add_gvcf_filters(opt,chrom_depth,os);


    std::string sample_name = determine_sample(bam_header_data);

    os << vcf_col_label() << "\tFORMAT\t" << sample_name << "\n";
}
