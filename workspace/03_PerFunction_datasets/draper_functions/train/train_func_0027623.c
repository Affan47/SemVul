stream_index_from_inputs(AVFormatContext **input_files,
                                    int nb_input_files,
                                    AVInputFile *file_table,
                                    AVInputStream **ist_table,
                                    enum CodecType type,
                                    int programid)
{
    int p, q, z;
    for(z=0; z<nb_input_files; z++) {
        AVFormatContext *ic = input_files[z];
        for(p=0; p<ic->nb_programs; p++) {
            AVProgram *program = ic->programs[p];
            if(program->id != programid)
                continue;
            for(q=0; q<program->nb_stream_indexes; q++) {
                int sidx = program->stream_index[q];
                int ris = file_table[z].ist_index + sidx;
                if(ist_table[ris]->discard && ic->streams[sidx]->codec->codec_type == type)
                    return ris;
            }
        }
    }

    return -1;
}
