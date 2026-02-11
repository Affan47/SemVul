mr_commit_i(IndexReader *ir)
{
    int i;
    const int mr_reader_cnt = MR(ir)->r_cnt;
    for (i = 0; i < mr_reader_cnt; i++) {
        IndexReader *reader = MR(ir)->sub_readers[i];
        ir_commit_i(reader);
    }
}
