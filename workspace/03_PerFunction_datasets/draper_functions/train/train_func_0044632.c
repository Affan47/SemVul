gt_contigs_writer_new(const GtEncseq *reads, GtFile *outfp,
    bool showpaths)
{
  GtContigsWriter *contigs_writer;

  gt_assert(reads != NULL);

  contigs_writer = gt_malloc(sizeof (GtContigsWriter));
  contigs_writer->reads = reads;
  contigs_writer->outfp = outfp;
  contigs_writer->showpaths = showpaths;
  contigs_writer->nofseqs = gt_encseq_num_of_sequences(contigs_writer->reads);
  contigs_writer->contignum = 0;
  contigs_writer->contigdepth = 0;
  GT_INITARRAY(&contigs_writer->contig, char);
  contigs_writer->contig_desc = gt_str_new();
  contigs_writer->path_desc = gt_str_new();
  contigs_writer->asc = gt_assembly_stats_calculator_new();
  contigs_writer->esr = gt_encseq_create_reader_with_readmode(reads,
      GT_READMODE_FORWARD, 0);
  return contigs_writer;
}
