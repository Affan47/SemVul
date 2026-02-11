generate_ki(DSRDocument *doc,
                        OFString &studyUID_ki)
{
    doc->createNewDocument(DSRTypes::DT_BasicTextSR);
    doc->getStudyInstanceUID(studyUID_ki);
    doc->setStudyDescription("OFFIS Structured Reporting Templates");
    doc->setSeriesDescription("IHE Year 2 - Key Image Note");
    doc->setSpecificCharacterSetType(DSRTypes::CS_Latin1);

    doc->setPatientName("Last Name^First Name");
    doc->setPatientSex("O");
    doc->setManufacturer("OFFIS e.V.");
    doc->setReferringPhysicianName("Last Name^First Name");

    doc->getTree().addContentItem(DSRTypes::RT_isRoot, DSRTypes::VT_Container);
    doc->getTree().getCurrentContentItem().setConceptName(DSRCodedEntryValue("IHE.01", OFFIS_CODING_SCHEME_DESIGNATOR, "Document Title"));

    doc->getTree().addContentItem(DSRTypes::RT_hasObsContext, DSRTypes::VT_Code, DSRTypes::AM_belowCurrent);
    doc->getTree().getCurrentContentItem().setConceptName(DSRCodedEntryValue("IHE.02", OFFIS_CODING_SCHEME_DESIGNATOR, "Observation Context Mode"));
    doc->getTree().getCurrentContentItem().setCodeValue(DSRCodedEntryValue("IHE.03", OFFIS_CODING_SCHEME_DESIGNATOR, "DIRECT"));
    doc->getTree().addContentItem(DSRTypes::RT_hasObsContext, DSRTypes::VT_PName);
    doc->getTree().getCurrentContentItem().setConceptName(DSRCodedEntryValue("IHE.04", OFFIS_CODING_SCHEME_DESIGNATOR, "Recording Observer's Name"));
    doc->getTree().getCurrentContentItem().setStringValue("Enter text");
    doc->getTree().addContentItem(DSRTypes::RT_hasObsContext, DSRTypes::VT_Text);
    doc->getTree().getCurrentContentItem().setConceptName(DSRCodedEntryValue("IHE.05", OFFIS_CODING_SCHEME_DESIGNATOR, "Recording Observer's Organization Name"));
    doc->getTree().getCurrentContentItem().setStringValue("Enter text");
    doc->getTree().addContentItem(DSRTypes::RT_hasObsContext, DSRTypes::VT_Code);
    doc->getTree().getCurrentContentItem().setConceptName(DSRCodedEntryValue("IHE.06", OFFIS_CODING_SCHEME_DESIGNATOR, "Observation Context Mode"));
    doc->getTree().getCurrentContentItem().setCodeValue(DSRCodedEntryValue("IHE.07", OFFIS_CODING_SCHEME_DESIGNATOR, "PATIENT"));

    doc->getTree().addContentItem(DSRTypes::RT_contains, DSRTypes::VT_Text);
    doc->getTree().getCurrentContentItem().setConceptName(DSRCodedEntryValue("IHE.11", OFFIS_CODING_SCHEME_DESIGNATOR, "Key Image Description"));
    doc->getTree().getCurrentContentItem().setStringValue("Enter text");

    doc->getTree().addContentItem(DSRTypes::RT_contains, DSRTypes::VT_Image);
    doc->getTree().getCurrentContentItem().setConceptName(DSRCodedEntryValue("IHE.10", OFFIS_CODING_SCHEME_DESIGNATOR, "Image Reference"));
    doc->getTree().getCurrentContentItem().setImageReference(DSRImageReferenceValue("0", "0"));
}
