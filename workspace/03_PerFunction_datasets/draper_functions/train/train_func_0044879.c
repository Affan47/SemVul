hbfile_cleanup(gboolean file_clear)
{
	DB( g_print("\n[hbfile] cleanup\n") );
	DB( g_print("- file clear is %d\n", file_clear) );


	da_acc_destroy();
	da_pay_destroy();
	da_cat_destroy();
	da_tag_destroy();
	da_asg_destroy();
	g_hash_table_destroy(GLOBALS->h_memo);
	da_archive_destroy(GLOBALS->arc_list);
	da_transaction_destroy(GLOBALS->ope_list);

	hbfile_change_owner(NULL);

	if(file_clear)
		hbfile_change_filepath(NULL);

}
