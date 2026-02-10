printOneChildRepr(raw_ostream &OS, const void *Ptr,
                              NodeKind Kind) const {
  switch (Kind) {
  case Twine::NullKind:
    OS << "null"; break;
  case Twine::EmptyKind:
    OS << "empty"; break;
  case Twine::TwineKind:
    OS << "rope:";
    static_cast<const Twine*>(Ptr)->printRepr(OS);
    break;
  case Twine::CStringKind:
    OS << "cstring:\""
       << static_cast<const char*>(Ptr) << "\"";
    break;
  case Twine::StdStringKind:
    OS << "std::string:\""
       << static_cast<const std::string*>(Ptr) << "\"";
    break;
  case Twine::StringRefKind:
    OS << "stringref:\""
       << static_cast<const StringRef*>(Ptr) << "\"";
    break;
  case Twine::DecUIKind:
    OS << "decUI:\"" << (unsigned)(uintptr_t)Ptr << "\"";
    break;
  case Twine::DecIKind:
    OS << "decI:\"" << (int)(intptr_t)Ptr << "\"";
    break;
  case Twine::DecULKind:
    OS << "decUL:\"" << *static_cast<const unsigned long*>(Ptr) << "\"";
    break;
  case Twine::DecLKind:
    OS << "decL:\"" << *static_cast<const long*>(Ptr) << "\"";
    break;
  case Twine::DecULLKind:
    OS << "decULL:\"" << *static_cast<const unsigned long long*>(Ptr) << "\"";
    break;
  case Twine::DecLLKind:
    OS << "decLL:\"" << *static_cast<const long long*>(Ptr) << "\"";
    break;
  case Twine::UHexKind:
    OS << "uhex:\"" << static_cast<const uint64_t*>(Ptr) << "\"";
    break;
  }
}
