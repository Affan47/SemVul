ToNode(RegExpCompiler* compiler,
                                        RegExpNode* on_success) {
  return new BackReferenceNode(RegExpCapture::StartRegister(index()),
                               RegExpCapture::EndRegister(index()),
                               on_success);
}
