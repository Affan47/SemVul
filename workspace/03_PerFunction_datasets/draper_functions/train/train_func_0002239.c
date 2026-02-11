errorCode() const
	{
		SecureMessage::Error e = SecureMessage::ErrorUnknown;
		if(op_err == GpgOp::ErrorProcess)
			e = SecureMessage::ErrorUnknown;
		else if(op_err == GpgOp::ErrorPassphrase)
			e = SecureMessage::ErrorPassphrase;
		else if(op_err == GpgOp::ErrorFormat)
			e = SecureMessage::ErrorFormat;
		else if(op_err == GpgOp::ErrorSignerExpired)
			e = SecureMessage::ErrorSignerExpired;
		else if(op_err == GpgOp::ErrorEncryptExpired)
			e = SecureMessage::ErrorEncryptExpired;
		else if(op_err == GpgOp::ErrorEncryptUntrusted)
			e = SecureMessage::ErrorEncryptUntrusted;
		else if(op_err == GpgOp::ErrorEncryptInvalid)
			e = SecureMessage::ErrorEncryptInvalid;
		else if(op_err == GpgOp::ErrorDecryptNoKey)
			e = SecureMessage::ErrorUnknown;
		else if(op_err == GpgOp::ErrorUnknown)
			e = SecureMessage::ErrorUnknown;
		return e;
	}
