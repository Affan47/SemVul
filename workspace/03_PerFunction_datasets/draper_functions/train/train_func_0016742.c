get_smart_status() const
{
	status_t status = status_unsupported;
	if (smart_enabled_.defined()) {
		if (smart_enabled_.value()) {
			status = status_enabled;
		} else {
			if (smart_supported_.defined()) {
				if (smart_supported_.value()) {
					status = status_disabled;
				} else {
					status = status_unsupported;
				}
			} else {
				status = status_disabled;
			}
		}
	} else {
		if (smart_supported_.defined()) {
			if (smart_supported_.value()) {
				status = status_disabled;
			} else {
				status = status_unsupported;
			}
		} else {
			status = status_unsupported;
		}
	}
	return status;
}
