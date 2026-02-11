ParseOptionalLinkage(unsigned &Res, bool &HasLinkage) {
  HasLinkage = false;
  switch (Lex.getKind()) {
  default:                       Res=GlobalValue::ExternalLinkage; return false;
  case lltok::kw_private:        Res = GlobalValue::PrivateLinkage;       break;
  case lltok::kw_linker_private: Res = GlobalValue::LinkerPrivateLinkage; break;
  case lltok::kw_linker_private_weak:
    Res = GlobalValue::LinkerPrivateWeakLinkage;
    break;
  case lltok::kw_linker_private_weak_def_auto:
    Res = GlobalValue::LinkerPrivateWeakDefAutoLinkage;
    break;
  case lltok::kw_internal:       Res = GlobalValue::InternalLinkage;      break;
  case lltok::kw_weak:           Res = GlobalValue::WeakAnyLinkage;       break;
  case lltok::kw_weak_odr:       Res = GlobalValue::WeakODRLinkage;       break;
  case lltok::kw_linkonce:       Res = GlobalValue::LinkOnceAnyLinkage;   break;
  case lltok::kw_linkonce_odr:   Res = GlobalValue::LinkOnceODRLinkage;   break;
  case lltok::kw_available_externally:
    Res = GlobalValue::AvailableExternallyLinkage;
    break;
  case lltok::kw_appending:      Res = GlobalValue::AppendingLinkage;     break;
  case lltok::kw_dllexport:      Res = GlobalValue::DLLExportLinkage;     break;
  case lltok::kw_common:         Res = GlobalValue::CommonLinkage;        break;
  case lltok::kw_dllimport:      Res = GlobalValue::DLLImportLinkage;     break;
  case lltok::kw_extern_weak:    Res = GlobalValue::ExternalWeakLinkage;  break;
  case lltok::kw_external:       Res = GlobalValue::ExternalLinkage;      break;
  }
  Lex.Lex();
  HasLinkage = true;
  return false;
}
