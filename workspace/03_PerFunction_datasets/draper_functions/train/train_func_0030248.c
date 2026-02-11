gt_ltr_fileout_stream_enable_pdom_alignment_output(GtNodeStream *ns)
{
  GtLTRFileOutStream *ls;
  gt_assert(ns);

  ls = gt_ltr_fileout_stream_cast(ns);
  ls->write_pdom_alignments = true;
}
