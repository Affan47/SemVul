gsb_data_account_get_init_balance ( gint account_number,
                        gint floating_point )
{
    struct_account *account;

    account = gsb_data_account_get_structure ( account_number );

    if (!account )
	return null_real;

    return gsb_real_adjust_exponent ( account -> init_balance,
				      floating_point );
}
