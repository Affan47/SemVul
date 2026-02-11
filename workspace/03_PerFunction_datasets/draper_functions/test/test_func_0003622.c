gnc_split_register_model_add_save_handlers (TableModel *model)
{
    g_return_if_fail (model != NULL);

    gnc_table_model_set_save_handler (model,
                                      gnc_split_register_save_date_cell,
                                      DATE_CELL);

    gnc_table_model_set_save_handler (model,
                                      gnc_split_register_save_due_date_cell,
                                      DDUE_CELL);

    gnc_table_model_set_save_handler (model,
                                      gnc_split_register_save_type_cell,
                                      TYPE_CELL);

    gnc_table_model_set_save_handler (model,
                                      gnc_split_register_save_num_cell,
                                      NUM_CELL);

    gnc_table_model_set_save_handler (model,
                                      gnc_split_register_save_tnum_cell,
                                      TNUM_CELL);

    gnc_table_model_set_save_handler (model,
                                      gnc_split_register_save_desc_cell,
                                      DESC_CELL);

    gnc_table_model_set_save_handler (model,
                                      gnc_split_register_save_notes_cell,
                                      NOTES_CELL);

    gnc_table_model_set_save_handler (model,
                                      gnc_split_register_save_recn_cell,
                                      RECN_CELL);

    gnc_table_model_set_save_handler (model,
                                      gnc_split_register_save_actn_cell,
                                      ACTN_CELL);

    gnc_table_model_set_save_handler (model,
                                      gnc_split_register_save_memo_cell,
                                      MEMO_CELL);

    gnc_table_model_set_save_handler (model,
                                      gnc_split_register_save_xfrm_cell,
                                      XFRM_CELL);

    gnc_table_model_set_save_handler (model,
                                      gnc_split_register_save_mxfrm_cell,
                                      MXFRM_CELL);

    gnc_table_model_set_save_handler (model,
                                      gnc_split_register_save_shares_cell,
                                      SHRS_CELL);

    gnc_table_model_set_save_handler (model,
                                      gnc_split_register_save_price_cell,
                                      PRIC_CELL);

    gnc_table_model_set_save_handler (model,
                                      gnc_split_register_save_debcred_cell,
                                      DEBT_CELL);

    gnc_table_model_set_save_handler (model,
                                      gnc_split_register_save_debcred_cell,
                                      CRED_CELL);

    gnc_table_model_set_save_handler (model,
                                      gnc_split_register_save_rate_cell,
                                      RATE_CELL);

    gnc_table_model_set_post_save_handler (model, gnc_split_register_save_cells);
}
