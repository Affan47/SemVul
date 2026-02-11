writeEntry(int, const PGPKey &key)
	{
		const MyPGPKeyContext *kc = static_cast<const MyPGPKeyContext *>(key.context());
		QByteArray buf = kc->toBinary();

		GpgOp gpg(find_bin());
		gpg.doImport(buf);
		gpg_waitForFinished(&gpg);
		gpg_keyStoreLog(gpg.readDiagnosticText());
		if(!gpg.success())
			return QString();

		return kc->_props.keyId;
	}
