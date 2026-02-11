free_GeneralName(GeneralName *data)
{
switch((data)->element) {
case choice_GeneralName_otherName:
der_free_oid(&(&(data)->u.otherName)->type_id);
free_heim_any(&(&(data)->u.otherName)->value);
break;
case choice_GeneralName_rfc822Name:
der_free_ia5_string(&(data)->u.rfc822Name);
break;
case choice_GeneralName_dNSName:
der_free_ia5_string(&(data)->u.dNSName);
break;
case choice_GeneralName_directoryName:
switch((&(data)->u.directoryName)->element) {
case choice_GeneralName_directoryName_rdnSequence:
free_RDNSequence(&(&(data)->u.directoryName)->u.rdnSequence);
break;
}
break;
case choice_GeneralName_uniformResourceIdentifier:
der_free_ia5_string(&(data)->u.uniformResourceIdentifier);
break;
case choice_GeneralName_iPAddress:
der_free_octet_string(&(data)->u.iPAddress);
break;
case choice_GeneralName_registeredID:
der_free_oid(&(data)->u.registeredID);
break;
}
}
