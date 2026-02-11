initClass()
{
    SO__ENGINE_INIT_CLASS(SoConvToTrigger,"SoConvToTrigger",SoFieldConverter);
    classTypeId.makeInternal();
    SoType trigType = SoSFTrigger::getClassTypeId();
    SoType conv = SoConvToTrigger::getClassTypeId();


    SoTypeList	fieldTypes;
    int		numFieldTypes;
    numFieldTypes = SoType::getAllDerivedFrom(SoField::getClassTypeId(),
					      fieldTypes);
    for (int i = 0; i < numFieldTypes; i++)
	if (fieldTypes[i] != trigType)
	    SoDB::addConverter(fieldTypes[i], trigType, conv);
}
