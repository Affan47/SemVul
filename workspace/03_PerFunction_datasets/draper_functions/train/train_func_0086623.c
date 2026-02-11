getFzpFilename(const QString & moduleID)
{
    QString filename = fzpPath() + moduleID + ".fzp";
    QFileInfo info(filename);
    if (info.exists()) return filename;

	if (moduleID.endsWith(ModuleIDNames::PerfboardModuleIDName)) {
		return getFzpFilenameAux(moduleID, &Perfboard::genFZP);
	}

	if (moduleID.endsWith(ModuleIDNames::StripboardModuleIDName)) {
		return getFzpFilenameAux(moduleID, &Stripboard::genFZP);
	}

	if (moduleID.endsWith(ModuleIDNames::Stripboard2ModuleIDName)) {
		return getFzpFilenameAux(moduleID, &Stripboard::genFZP);
	}

	if (moduleID.startsWith("generic_ic_dip")) {
		return getFzpFilenameAux(moduleID, &Dip::genDipFZP);
	}

	if (moduleID.startsWith("screw_terminal")) {
		return getFzpFilenameAux(moduleID, &ScrewTerminal::genFZP);
	}

	if (moduleID.startsWith("generic_sip")) {
		return getFzpFilenameAux(moduleID, &Dip::genSipFZP);
	}

	if (moduleID.contains("_pin_header_") && moduleID.startsWith("generic_")) {
		return getFzpFilenameAux(moduleID, &PinHeader::genFZP);
	}

	if (moduleID.startsWith("mystery_part")) {
		if (moduleID.contains("dip", Qt::CaseInsensitive)) {
			return getFzpFilenameAux(moduleID, &MysteryPart::genDipFZP);
		}
		else {
			return getFzpFilenameAux(moduleID, &MysteryPart::genSipFZP);
		}
	}

	return "";
}
