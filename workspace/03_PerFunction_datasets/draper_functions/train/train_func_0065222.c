operator<< (std::ostream &out, Poppler::FormField::FormType type)
{
    switch (type) {
        case Poppler::FormField::FormButton:    out << "Button";    break;
        case Poppler::FormField::FormText:      out << "Text";      break;
        case Poppler::FormField::FormChoice:    out << "Choice";    break;
        case Poppler::FormField::FormSignature: out << "Signature"; break;
    }
    return out;
}
