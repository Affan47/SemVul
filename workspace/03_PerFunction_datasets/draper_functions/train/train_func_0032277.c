lose_exp(s32b amount)
{

	if (amount > p_ptr->exp) amount = p_ptr->exp;


	p_ptr->exp -= amount;


	check_experience();
}
