setLevel(Logger::Level level)
{
    if (this->_level == level)
        return ;
    *(this->_output) << "[" << this->_level_strings[Logger::LVL_INFO] << "] "
        << "Changing logger level from '"
        << this->_level_strings[this->_level]
        << "' to '"
        << this->_level_strings[level]
        << "'" << std::endl;
    this->_level = level;
}
