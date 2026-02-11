csv_import_trans_assistant_finish (GtkAssistant *assistant, gpointer user_data)
{
    CsvImportTrans *info = user_data;


    if (info->parse_data->transactions != NULL)
        gnc_gen_trans_assist_start(info->gnc_csv_importer_gui);
    else
        gnc_gen_trans_list_delete(info->gnc_csv_importer_gui);
}
