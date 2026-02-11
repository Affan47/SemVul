init(const std::string& dir, char c)
{
    m_c = c;
    m_file_name = dir+"buffered_char_queue_"+util::to_string(util::get_id());

}
