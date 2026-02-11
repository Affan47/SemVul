ff_real_parse_sdp_a_line (AVFormatContext *s, int stream_index,
                          const char *line)
{
    const char *p = line;

    if (av_strstart(p, "ASMRuleBook:string;", &p))
        real_parse_asm_rulebook(s, s->streams[stream_index], p);
}
