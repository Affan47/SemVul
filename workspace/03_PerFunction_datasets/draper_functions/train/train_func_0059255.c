bc_rs_close_stream(struct bc_read_stream *stream)
{
    free(stream->record_abbrev_operands);
    free(stream->record_buf);
    free(stream->abbrev_operands);
    free(stream->stream_stack);

    for(int i = 0; i < stream->blockinfo_len; i++)
    {
        for(int j = 0; j < stream->blockinfos[i].num_abbreviations; j++)
        {
            free(stream->blockinfos[i].abbreviations[j].operands);
        }
        free(stream->blockinfos[i].abbreviations);
    }
    free(stream->blockinfos);

    if(stream->infile)
        fclose(stream->infile);
    free(stream);
}
