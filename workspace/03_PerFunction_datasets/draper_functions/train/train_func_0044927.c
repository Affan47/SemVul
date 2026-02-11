H5HF_dtable_span_size(const H5HF_dtable_t *dtable, unsigned start_row,
    unsigned start_col, unsigned num_entries)
{
    unsigned start_entry;
    unsigned end_row;
    unsigned end_col;
    unsigned end_entry;
    hsize_t acc_span_size;

    FUNC_ENTER_NOAPI_NOINIT_NOERR


    HDassert(dtable);
    HDassert(num_entries > 0);


    start_entry = (start_row * dtable->cparam.width) + start_col;


    end_entry = (start_entry + num_entries) - 1;
    end_row = end_entry / dtable->cparam.width;
    end_col = end_entry % dtable->cparam.width;
#ifdef QAK
HDfprintf(stderr, "%s: start_row = %u, start_col = %u, start_entry = %u\n", "H5HF_sect_indirect_span_size", start_row, start_col, start_entry);
HDfprintf(stderr, "%s: end_row = %u, end_col = %u, end_entry = %u\n", "H5HF_sect_indirect_span_size", end_row, end_col, end_entry);
#endif


    acc_span_size = 0;


    if(start_row != end_row) {

        if(start_col > 0) {
            acc_span_size = dtable->row_block_size[start_row] *
                    (dtable->cparam.width - start_col);
            start_row++;
        }


        while(start_row < end_row) {
            acc_span_size += dtable->row_block_size[start_row] *
                    dtable->cparam.width;
            start_row++;
        }


        acc_span_size += dtable->row_block_size[start_row] *
                (end_col + 1);
    }
    else {

        acc_span_size = dtable->row_block_size[start_row] *
                ((end_col - start_col) + 1);
    }

#ifdef QAK
HDfprintf(stderr, "%s: acc_span_size = %Hu\n", "H5HF_dtable_span_size", acc_span_size);
#endif
    FUNC_LEAVE_NOAPI(acc_span_size)
}
