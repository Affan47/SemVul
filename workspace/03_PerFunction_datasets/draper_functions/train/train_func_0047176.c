statusForTarget(cmTarget *tgt, const char *policy)
{
#define RETURN_POLICY(POLICY) \
  if (strcmp(policy, #POLICY) == 0) \
  { \
    return tgt->GetPolicyStatus ## POLICY (); \
  } \

  CM_FOR_EACH_TARGET_POLICY(RETURN_POLICY)

#undef RETURN_POLICY

  assert("!Unreachable code. Not a valid policy");
  return cmPolicies::WARN;
}
