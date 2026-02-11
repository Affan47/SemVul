CopyFnCall(struct FnCall *f)

{
Debug("CopyFnCall()\n");
return NewFnCall(f->name,CopyRlist(f->args));
}
