free_HDB_extension(HDB_extension *data)
{
switch((&(data)->data)->element) {
case choice_HDB_extension_data_pkinit_acl:
free_HDB_Ext_PKINIT_acl(&(&(data)->data)->u.pkinit_acl);
break;
case choice_HDB_extension_data_pkinit_cert_hash:
free_HDB_Ext_PKINIT_hash(&(&(data)->data)->u.pkinit_cert_hash);
break;
case choice_HDB_extension_data_allowed_to_delegate_to:
free_HDB_Ext_Constrained_delegation_acl(&(&(data)->data)->u.allowed_to_delegate_to);
break;
case choice_HDB_extension_data_lm_owf:
free_HDB_Ext_Lan_Manager_OWF(&(&(data)->data)->u.lm_owf);
break;
case choice_HDB_extension_data_password:
free_HDB_Ext_Password(&(&(data)->data)->u.password);
break;
case choice_HDB_extension_data_aliases:
free_HDB_Ext_Aliases(&(&(data)->data)->u.aliases);
break;
case choice_HDB_extension_data_last_pw_change:
free_KerberosTime(&(&(data)->data)->u.last_pw_change);
break;
case choice_HDB_extension_data_pkinit_cert:
free_HDB_Ext_PKINIT_cert(&(&(data)->data)->u.pkinit_cert);
break;
case choice_HDB_extension_data_hist_keys:
free_HDB_Ext_KeySet(&(&(data)->data)->u.hist_keys);
break;
case choice_HDB_extension_data_hist_kvno_diff_clnt:
break;
case choice_HDB_extension_data_hist_kvno_diff_svc:
break;
case choice_HDB_extension_data_policy:
der_free_utf8string(&(&(data)->data)->u.policy);
break;
case choice_HDB_extension_data_principal_id:
break;
case choice_HDB_extension_data_asn1_ellipsis:
der_free_octet_string(&(&(data)->data)->u.asn1_ellipsis);
break;}
}
