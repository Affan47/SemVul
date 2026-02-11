replaceFunctionDeclName(const FunctionDecl *FD,
                                      const std::string &NameStr)
{


  DeclarationNameInfo NameInfo = FD->getNameInfo();
  DeclarationName DeclName = NameInfo.getName();
  DeclarationName::NameKind K = DeclName.getNameKind();
  TransAssert((K != DeclarationName::CXXDestructorName) &&
              "Cannot rename CXXDestructorName here!");

  std::string FDName = FD->getNameAsString();
  size_t FDNameLen = FD->getNameAsString().length();
  if (K == DeclarationName::CXXConstructorName) {
    const Type *Ty = DeclName.getCXXNameType().getTypePtr();
    if (Ty->getTypeClass() == Type::InjectedClassName) {
      const CXXRecordDecl *CXXRD = Ty->getAsCXXRecordDecl();
      std::string RDName = CXXRD->getNameAsString();
      FDNameLen = FDName.find(RDName);
      TransAssert((FDNameLen != std::string::npos) &&
                  "Cannot find RecordDecl Name!");
      FDNameLen += RDName.length();
    }
  }

  return !TheRewriter->ReplaceText(NameInfo.getLoc(),
                                   FDNameLen,
                                   NameStr);
}
