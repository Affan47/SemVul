remove_program(unsigned char number) {
  std::map<int, string>::iterator iter = m_programs.find(number);
  if (iter != m_programs.end()) {
    m_programs.erase(iter);
    update_program_menu();
  }
}
