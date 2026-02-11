nscope(CObjectInfo *obj) {

  if (obj->TemplateInstance ())
    obj = obj->TemplateInstance ()->Template ();

  CRecord *crec = obj->ClassScope ();
  CScopeInfo *qual = obj->QualifiedScope ();
  CScopeInfo *scope = obj->Scope ();
  return crec ? (CScopeInfo*)crec : (qual ? qual : (scope->GlobalScope () ? 0 :
scope));
}
