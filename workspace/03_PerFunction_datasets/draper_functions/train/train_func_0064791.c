ml_gdome_di_saveDocumentToFile(value self, value doc, value name, value mode)
{
  CAMLparam4(self, doc, name, mode);
  GdomeException exc_;
  GdomeBoolean res_;
  res_ = gdome_di_saveDocToFile(DOMImplementation_val(self), Document_val(doc), String_val(name), Int_val(mode), &exc_);
  if (exc_ != 0) throw_exception(exc_, "DOMImplementation.saveDocToFile");
  CAMLreturn(Val_bool(res_));
}
