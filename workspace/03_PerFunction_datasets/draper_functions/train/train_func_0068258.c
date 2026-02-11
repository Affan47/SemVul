pet_performance_val(struct map_session_data *sd)
{
	nullpo_retr(0, sd);

	if(sd->pet.intimate > 900)
		return (sd->petDB->s_perfor > 0)? 4: 3;
	if(sd->pet.intimate > 750)
		return 2;

	return 1;
}
