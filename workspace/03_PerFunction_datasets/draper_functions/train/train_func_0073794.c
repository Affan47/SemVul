branch_comparison_operator (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
{
  return (comparison_operator (op, mode)) && ((
#line 1195 "../../src/gcc/config/rs6000/predicates.md"
(GET_MODE_CLASS (GET_MODE (XEXP (op, 0))) == MODE_CC)) && (
#line 1196 "../../src/gcc/config/rs6000/predicates.md"
(validate_condition_mode (GET_CODE (op),
						   GET_MODE (XEXP (op, 0))),
			  1)));
}
