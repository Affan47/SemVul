test_vcard_qp_3_0_saving (const gchar *expected_text)
{
	EVCard *vcard;
	EVCardAttribute *attr;
	EVCardAttributeParam *param;
	gchar *str, *value, *encoded_value;
	GString *decoded;

	vcard = e_vcard_new ();
	attr = e_vcard_attribute_new (NULL, "FN");
	param = e_vcard_attribute_param_new ("ENCODING");
	e_vcard_attribute_param_add_value (param, "quoted-printable");
	e_vcard_attribute_add_param (attr, param);

	e_vcard_attribute_add_value_decoded (attr, expected_text, strlen (expected_text));
	e_vcard_add_attribute (vcard, attr);

	decoded = e_vcard_attribute_get_value_decoded (attr);
	g_return_val_if_fail (decoded != NULL, FALSE);
	g_return_val_if_fail (g_strcmp0 (decoded->str, expected_text) == 0, FALSE);
	g_string_free (decoded, TRUE);

	encoded_value = e_vcard_attribute_get_value (attr);
	g_return_val_if_fail (encoded_value != NULL, FALSE);

	g_return_val_if_fail (g_strcmp0 (encoded_value, expected_text) != 0, FALSE);

	str = e_vcard_to_string (vcard, EVC_FORMAT_VCARD_30);

	g_object_unref (vcard);

	g_return_val_if_fail (str != NULL, FALSE);

	vcard = e_vcard_new_from_string (str);
	g_free (str);

	g_return_val_if_fail (vcard != NULL, FALSE);

	attr = e_vcard_get_attribute (vcard, "FN");
	g_return_val_if_fail (attr != NULL, FALSE);

	decoded = e_vcard_attribute_get_value_decoded (attr);
	g_return_val_if_fail (decoded != NULL, FALSE);
	g_return_val_if_fail (g_strcmp0 (decoded->str, expected_text) == 0, FALSE);
	g_string_free (decoded, TRUE);

	value = e_vcard_attribute_get_value (attr);
	g_return_val_if_fail (value != NULL, FALSE);

	g_return_val_if_fail (g_strcmp0 (value, encoded_value) != 0, FALSE);
	g_free (value);

	g_object_unref (vcard);
	g_free (encoded_value);

	return TRUE;
}
