gdata_contacts_contact_set_property (GObject *object, guint property_id, const GValue *value, GParamSpec *pspec)
{
	GDataContactsContact *self = GDATA_CONTACTS_CONTACT (object);

	switch (property_id) {
		case PROP_NAME:
			gdata_contacts_contact_set_name (self, g_value_get_object (value));
			break;
		case PROP_NICKNAME:
			gdata_contacts_contact_set_nickname (self, g_value_get_string (value));
			break;
		case PROP_FILE_AS:
			gdata_contacts_contact_set_file_as (self, g_value_get_string (value));
			break;
		case PROP_BIRTHDAY:
			gdata_contacts_contact_set_birthday (self, g_value_get_boxed (value), self->priv->birthday_has_year);
			break;
		case PROP_BIRTHDAY_HAS_YEAR:
			gdata_contacts_contact_set_birthday (self, &(self->priv->birthday), g_value_get_boolean (value));
			break;
		case PROP_BILLING_INFORMATION:
			gdata_contacts_contact_set_billing_information (self, g_value_get_string (value));
			break;
		case PROP_DIRECTORY_SERVER:
			gdata_contacts_contact_set_directory_server (self, g_value_get_string (value));
			break;
		case PROP_GENDER:
			gdata_contacts_contact_set_gender (self, g_value_get_string (value));
			break;
		case PROP_INITIALS:
			gdata_contacts_contact_set_initials (self, g_value_get_string (value));
			break;
		case PROP_MAIDEN_NAME:
			gdata_contacts_contact_set_maiden_name (self, g_value_get_string (value));
			break;
		case PROP_MILEAGE:
			gdata_contacts_contact_set_mileage (self, g_value_get_string (value));
			break;
		case PROP_OCCUPATION:
			gdata_contacts_contact_set_occupation (self, g_value_get_string (value));
			break;
		case PROP_PRIORITY:
			gdata_contacts_contact_set_priority (self, g_value_get_string (value));
			break;
		case PROP_SENSITIVITY:
			gdata_contacts_contact_set_sensitivity (self, g_value_get_string (value));
			break;
		case PROP_SHORT_NAME:
			gdata_contacts_contact_set_short_name (self, g_value_get_string (value));
			break;
		case PROP_SUBJECT:
			gdata_contacts_contact_set_subject (self, g_value_get_string (value));
			break;
		default:

			G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
			break;
	}
}
