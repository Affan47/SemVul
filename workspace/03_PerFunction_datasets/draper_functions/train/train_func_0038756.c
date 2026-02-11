tls_symbolic_operand (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
{
  return (GET_CODE (op) == SYMBOL_REF) && (
#line 498 "../../src/gcc/config/i386/predicates.md"
(SYMBOL_REF_TLS_MODEL (op)));
}
