Void_delete(DOH *vo) {
  VoidObj *v = (VoidObj *) ObjData(vo);
  if (v->del)
    (*v->del) (v->ptr);
  DohFree(v);
}
