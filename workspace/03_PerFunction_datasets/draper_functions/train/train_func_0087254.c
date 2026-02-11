AddSequenceHeader(SequenceHeaderByteIO *p_seqheader_byteio)
{

    ParseUnitByteIO *mp_previous_parse_unit=mp_prev_parse_unit;

    if(!m_parse_unit_list.empty())
        mp_previous_parse_unit = m_parse_unit_list.back().second;


    p_seqheader_byteio->SetAdjacentParseUnits(mp_previous_parse_unit);


    m_parse_unit_list.push(std::make_pair (PU_SEQ_HEADER, p_seqheader_byteio) );


    mp_previous_parse_unit = p_seqheader_byteio;


    p_seqheader_byteio->CollateByteStats(m_sequence_stats);
}
