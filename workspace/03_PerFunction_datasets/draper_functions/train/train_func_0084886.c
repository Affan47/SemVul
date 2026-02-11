operatorEqReturnError(const Token *tok, const std::string &className)
{
    reportError(tok, Severity::style, "operatorEq", "'" + className + "::operator=' should return '" + className + " &'.\n"
                "The "+className+"::operator= does not conform to standard C/C++ behaviour. To conform to standard C/C++ behaviour, return a reference to self (such as: '"+className+" &"+className+"::operator=(..) { .. return *this; }'. For safety reasons it might be better to not fix this message. If you think that safety is always more important than conformance then please ignore/suppress this message. For more details about this topic, see the book \"Effective C++\" by Scott Meyers."
               );
}
