SetValues(const std::vector<std::string>& val)
   {
     Clear_p(this->m_Format, this->m_Values);
     this->FillDimensions(val);
     this->m_Format = Char;
     std::vector<std::string> values = val;
     this->FillSource(values);
     Voidify_p(values, this->m_Values);
   }
