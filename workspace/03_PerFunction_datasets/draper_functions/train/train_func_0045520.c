GenerateScript(std::ostream& os)
{
  Indent indent;
  std::string component_test =
    this->CreateComponentTest(this->Component.c_str());
  os << indent << "IF(" << component_test << ")\n";

  if(this->Code)
    {
    os << indent.Next() << this->Script << "\n";
    }
  else
    {
    os << indent.Next() << "INCLUDE(\"" << this->Script << "\")\n";
    }

  os << indent << "ENDIF(" << component_test << ")\n\n";
}
