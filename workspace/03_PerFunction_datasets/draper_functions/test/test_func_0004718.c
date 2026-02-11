delete_ansi_tcap_subdissector(guint32 ssn, dissector_handle_t dissector _U_) {
    g_hash_table_remove(ansi_sub_dissectors,GUINT_TO_POINTER(ssn));
    if (!get_itu_tcap_subdissector(ssn))
      dissector_delete_uint("sccp.ssn",ssn,tcap_handle);
}
