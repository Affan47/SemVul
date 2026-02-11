operator>>=(const ::CORBA::Any& _a, const CosExternalization::ContextAlreadyRegistered*& _sp)
{
  void* _v;
  if (_a.PR_extract(_0RL_tc_CosExternalization_mContextAlreadyRegistered,
                    _0RL_CosExternalization_mContextAlreadyRegistered_unmarshal_fn,
                    _0RL_CosExternalization_mContextAlreadyRegistered_marshal_fn,
                    _0RL_CosExternalization_mContextAlreadyRegistered_destructor_fn,
                    _v)) {
    _sp = (const CosExternalization::ContextAlreadyRegistered*)_v;
    return 1;
  }
  return 0;
}
