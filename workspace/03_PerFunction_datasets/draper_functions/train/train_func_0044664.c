gt_fasta_reader_run(GtFastaReader *fr,
                     GtFastaReaderProcDescription proc_description,
                     GtFastaReaderProcSequencePart proc_sequence_part,
                     GtFastaReaderProcSequenceLength proc_sequence_length,
                     void *data, GtError *err)
{
  gt_error_check(err);
  gt_assert(fr && fr->c_class && fr->c_class->run);
  return fr->c_class->run(fr, proc_description, proc_sequence_part,
                          proc_sequence_length, data, err);
}
