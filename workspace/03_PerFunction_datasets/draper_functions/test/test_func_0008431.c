av_close_input_stream(AVFormatContext *s)
{
    int i;
    AVStream *st;

    if (s->iformat->read_close)
        s->iformat->read_close(s);
    for(i=0;i<s->nb_streams;i++) {

        st = s->streams[i];
        if (st->parser) {
            av_parser_close(st->parser);
            av_free_packet(&st->cur_pkt);
        }
        av_metadata_free(&st->metadata);
        av_free(st->index_entries);
        av_free(st->codec->extradata);
        av_free(st->codec);
#if LIBAVFORMAT_VERSION_INT < (53<<16)
        av_free(st->filename);
#endif
        av_free(st->priv_data);
        av_free(st);
    }
    for(i=s->nb_programs-1; i>=0; i--) {
#if LIBAVFORMAT_VERSION_INT < (53<<16)
        av_freep(&s->programs[i]->provider_name);
        av_freep(&s->programs[i]->name);
#endif
        av_metadata_free(&s->programs[i]->metadata);
        av_freep(&s->programs[i]->stream_index);
        av_freep(&s->programs[i]);
    }
    av_freep(&s->programs);
    flush_packet_queue(s);
    av_freep(&s->priv_data);
    while(s->nb_chapters--) {
#if LIBAVFORMAT_VERSION_INT < (53<<16)
        av_free(s->chapters[s->nb_chapters]->title);
#endif
        av_metadata_free(&s->chapters[s->nb_chapters]->metadata);
        av_free(s->chapters[s->nb_chapters]);
    }
    av_freep(&s->chapters);
    av_metadata_free(&s->metadata);
    av_free(s);
}
