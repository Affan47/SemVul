coalescable_pseudo_p (int regno)
{
  lra_assert (regno >= FIRST_PSEUDO_REGISTER);
  return (

	  ira_reg_equiv[regno].constant == NULL_RTX
	  && ira_reg_equiv[regno].memory == NULL_RTX
	  && ira_reg_equiv[regno].invariant == NULL_RTX);
}
