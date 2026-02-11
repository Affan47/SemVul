add_immunity(artifact_type *a_ptr)
{
	int imm_type = randint0(4);

	switch(imm_type)
	{
		case 0:
		{
			of_on(a_ptr->flags, OF_IM_ACID);
			LOG_PRINT("Adding ability: immunity to acid\n");
			break;
		}
		case 1:
		{
			of_on(a_ptr->flags, OF_IM_ELEC);
			LOG_PRINT("Adding ability: immunity to lightning\n");
			break;
		}
		case 2:
		{
			of_on(a_ptr->flags, OF_IM_FIRE);
			LOG_PRINT("Adding ability: immunity to fire\n");
			break;
		}
		case 3:
		{
			of_on(a_ptr->flags, OF_IM_COLD);
			LOG_PRINT("Adding ability: immunity to cold\n");
			break;
		}
	}
}
