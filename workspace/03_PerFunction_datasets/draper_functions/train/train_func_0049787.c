cxx_readonly_error (tree arg, enum lvalue_use errstring)
{


#define ERROR_FOR_ASSIGNMENT(AS, ASM, IN, DE, ARG)                      \
  do {                                                                  \
    switch (errstring)                                                  \
      {                                                                 \
      case lv_assign:							\
        error(AS, ARG);                                                 \
        break;                                                          \
      case lv_asm:							\
        error(ASM, ARG);                                                \
        break;                                                          \
      case lv_increment:						\
        error (IN, ARG);                                                \
        break;                                                          \
      case lv_decrement:                                               \
        error (DE, ARG);                                                \
        break;                                                          \
      default:                                                          \
        gcc_unreachable ();                                             \
      }                                                                 \
  } while (0)


  if (TREE_CODE (arg) == VAR_DECL
      && DECL_LANG_SPECIFIC (arg)
      && DECL_IN_AGGR_P (arg)
      && !TREE_STATIC (arg))
    ERROR_FOR_ASSIGNMENT (G_("assignment of "
			     "constant field %qD"),
			  G_("constant field %qD "
			     "used as %<asm%> output"),
			  G_("increment of "
			     "constant field %qD"),
			  G_("decrement of "
			     "constant field %qD"),
			  arg);
  else if (TREE_CODE (arg) == INDIRECT_REF
	   && TREE_CODE (TREE_TYPE (TREE_OPERAND (arg, 0))) == REFERENCE_TYPE
	   && (TREE_CODE (TREE_OPERAND (arg, 0)) == VAR_DECL
	       || TREE_CODE (TREE_OPERAND (arg, 0)) == PARM_DECL))
    ERROR_FOR_ASSIGNMENT (G_("assignment of "
                             "read-only reference %qD"),
                          G_("read-only reference %qD "
			     "used as %<asm%> output"),
                          G_("increment of "
                             "read-only reference %qD"),
                          G_("decrement of "
                             "read-only reference %qD"),
                          TREE_OPERAND (arg, 0));
  else
    readonly_error (arg, errstring);
}
