arm_print_operand_punct_valid_p (unsigned char code)
{
  return (code == '@' || code == '|' || code == '.'
	  || code == '(' || code == ')' || code == '#'
	  || (TARGET_32BIT && (code == '?'))
	  || (TARGET_THUMB2 && (code == '!'))
	  || (TARGET_THUMB && (code == '_')));
}
