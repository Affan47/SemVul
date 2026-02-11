pushHandler(const StartCB_t &start,
                                  const DataCB_t &data,
                                  const EndCB_t &end)
{
    m_stack.push_back(Callbacks(start, data, end));
    Callbacks &cb = m_stack.back();
    ne_xml_push_handler(m_parser,
                        startCB, dataCB, endCB,
                        &cb);
    return *this;
}
