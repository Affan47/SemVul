gt_stream_evaluator_show(GtStreamEvaluator *se, GtFile *outfp)
{
  gt_assert(se);

  if (!se->evalLTR) {

    gt_file_xprintf(outfp, "gene sensitivity (mRNA level): ");
    gt_evaluator_show_sensitivity(se->mRNA_gene_evaluator, outfp);
    gt_file_xprintf(outfp, " (missing genes: %lu)\n", se->missing_genes);

    gt_file_xprintf(outfp, "gene specificity (mRNA level): ");
    gt_evaluator_show_specificity(se->mRNA_gene_evaluator, outfp);
    gt_file_xprintf(outfp, " (wrong genes: %lu)\n", se->wrong_genes);

    gt_file_xprintf(outfp, "gene sensitivity (CDS level): ");
    gt_evaluator_show_sensitivity(se->CDS_gene_evaluator, outfp);
    gt_file_xprintf(outfp, " (missing genes: %lu)\n", se->missing_genes);

    gt_file_xprintf(outfp, "gene specificity (CDS level): ");
    gt_evaluator_show_specificity(se->CDS_gene_evaluator, outfp);
    gt_file_xprintf(outfp, " (wrong genes: %lu)\n", se->wrong_genes);


    gt_file_xprintf(outfp, "mRNA sensitivity (mRNA level): ");
    gt_evaluator_show_sensitivity(se->mRNA_mRNA_evaluator, outfp);
    gt_file_xprintf(outfp, " (missing mRNAs: %lu)\n", se->missing_mRNAs);

    gt_file_xprintf(outfp, "mRNA specificity (mRNA level): ");
    gt_evaluator_show_specificity(se->mRNA_mRNA_evaluator, outfp);
    gt_file_xprintf(outfp, " (wrong mRNAs: %lu)\n", se->wrong_mRNAs);

    gt_file_xprintf(outfp, "mRNA sensitivity (CDS level): ");
    gt_evaluator_show_sensitivity(se->CDS_mRNA_evaluator, outfp);
    gt_file_xprintf(outfp, " (missing mRNAs: %lu)\n", se->missing_mRNAs);

    gt_file_xprintf(outfp, "mRNA specificity (CDS level): ");
    gt_evaluator_show_specificity(se->CDS_mRNA_evaluator, outfp);
    gt_file_xprintf(outfp, " (wrong mRNAs: %lu)\n", se->wrong_mRNAs);


    show_transcript_values(se->mRNA_exon_evaluators, "mRNA", "", outfp);
    show_transcript_values(se->mRNA_exon_evaluators_collapsed, "mRNA",
                           ", collapsed", outfp);


    show_transcript_values(se->CDS_exon_evaluators, "CDS", "", outfp);
    show_transcript_values(se->CDS_exon_evaluators_collapsed, "CDS",
                           ", collapsed", outfp);

    if (se->nuceval) {

      show_nucleotide_values(&se->mRNA_nucleotides, "mRNA", outfp);

      show_nucleotide_values(&se->CDS_nucleotides, "CDS", outfp);
    }
  }
  else {

    gt_file_xprintf(outfp, "LTR_retrotransposon sensitivity: ");
    gt_evaluator_show_sensitivity(se->LTR_evaluator, outfp);
    gt_file_xprintf(outfp, " (missing LTRs: %lu)\n", se->missing_LTRs);

    gt_file_xprintf(outfp, "LTR_retrotransposon specificity: ");
    gt_evaluator_show_specificity(se->LTR_evaluator, outfp);
    gt_file_xprintf(outfp, " (wrong LTRs: %lu)\n", se->wrong_LTRs);
  }
}
