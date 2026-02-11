brasero_burn_eject (BraseroBurn *self,
		    BraseroDrive *drive,
		    GError **error)
{
	guint counter = 0;
	BraseroMedium *medium;
	BraseroBurnResult result;

	BRASERO_BURN_LOG ("Ejecting drive/medium");


	medium = brasero_drive_get_medium (drive);
	result = brasero_burn_unmount (self, medium, error);
	if (result != BRASERO_BURN_OK)
		return result;


	if (brasero_drive_is_locked (drive, NULL)) {
		if (!brasero_drive_unlock (drive)) {
			gchar *name;

			name = brasero_drive_get_display_name (drive);
			g_set_error (error,
				     BRASERO_BURN_ERROR,
				     BRASERO_BURN_ERROR_GENERAL,
				     _("\"%s\" cannot be unlocked"),
				     name);
			g_free (name);
			return BRASERO_BURN_ERR;
		}
	}


	while (brasero_drive_get_medium (drive) || brasero_drive_probing (drive)) {
		GError *ret_error;


		if (brasero_drive_probing (drive)) {
			result = brasero_burn_sleep (self, 500);
			if (result != BRASERO_BURN_OK)
				return result;

			continue;
		}

		counter ++;
		if (counter == 1)
			brasero_burn_action_changed_real (self, BRASERO_BURN_ACTION_EJECTING);

		if (counter > MAX_EJECT_ATTEMPTS) {
			BRASERO_BURN_LOG ("Max attempts reached at ejecting");

			result = brasero_burn_emit_eject_failure_signal (self, drive);
			if (result != BRASERO_BURN_OK)
				return result;

			continue;
		}

		BRASERO_BURN_LOG ("Retrying ejection");
		ret_error = NULL;
		brasero_drive_eject (drive, TRUE, &ret_error);

		if (ret_error) {
			BRASERO_BURN_LOG ("Ejection error: %s", ret_error->message);
			g_error_free (ret_error);
		}

		result = brasero_burn_sleep (self, 500);
		if (result != BRASERO_BURN_OK)
			return result;
	}

	return BRASERO_BURN_OK;
}
