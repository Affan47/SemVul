makeSchematicSipOrDipOr(const QStringList & labels, bool hasLayout, bool sip)
{
	if (hasLayout) {
		return MysteryPart::makeSchematicSvg(labels, false);
	}

    if (sip) {
		return MysteryPart::makeSchematicSvg(labels, true);
	}

	return Dip::makeSchematicSvg(labels);
}
