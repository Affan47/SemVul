endLink()
{
  if (--linkDepth_ == 0) {
    if (havePendingLink_)
      havePendingLink_ = 0;
    else {
      os() << (rtfVersion_ >= word97 ? "}}" : "}{\\fldrslt }}");
      outputFormat_ = saveOutputFormat_;
    }
  }
  end();
}
