generate_01(DSRDocument *doc, OFString &studyUID_01)
{
    doc->createNewDocument(DSRTypes::DT_BasicTextSR);
    doc->setStudyDescription("OFFIS Structured Reporting Samples");
    doc->getStudyInstanceUID(studyUID_01);
    doc->setSeriesDescription("Basic Text Report");

    doc->setPatientName("Osterman^Phillip^B.");
    doc->setPatientBirthDate("19220909");
    doc->setPatientSex("M");
    doc->setReferringPhysicianName("Fukuda^Katherine M.^^^M. D.");

    doc->getTree().addContentItem(DSRTypes::RT_isRoot, DSRTypes::VT_Container);
    doc->getTree().getCurrentContentItem().setConceptName(DSRCodedEntryValue("DT.06", OFFIS_CODING_SCHEME_DESIGNATOR, "Consultation Report"));

    doc->getTree().addContentItem(DSRTypes::RT_hasObsContext, DSRTypes::VT_PName, DSRTypes::AM_belowCurrent);
    doc->getTree().getCurrentContentItem().setConceptName(DSRCodedEntryValue("IHE.04", OFFIS_CODING_SCHEME_DESIGNATOR, "Observer Name"));
    doc->getTree().getCurrentContentItem().setStringValue("Packer^David M.^^^M. D.");
    doc->getTree().addContentItem(DSRTypes::RT_hasObsContext, DSRTypes::VT_Text);
    doc->getTree().getCurrentContentItem().setConceptName(DSRCodedEntryValue("IHE.05", OFFIS_CODING_SCHEME_DESIGNATOR, "Observer Organization Name"));
    doc->getTree().getCurrentContentItem().setStringValue("Redlands Clinic");

    doc->getTree().addContentItem(DSRTypes::RT_contains, DSRTypes::VT_Text);
    doc->getTree().getCurrentContentItem().setConceptName(DSRCodedEntryValue("CODE_01", OFFIS_CODING_SCHEME_DESIGNATOR, "Description"));
    doc->getTree().getCurrentContentItem().setStringValue("This 78-year-old gentleman referred by Dr. Fukuda was also seen by Dr. Mason at the Redlands Clinic. He has been seen in the past by Dr. Klugman.\nThe patient developed a lesion in the concha of the left external ear. Recent biopsy confirmed this as being a squamous cell carcinoma. The patient has had a few other skin cancers.\nOf most significant past history is the fact that this patient has a leukemia that has been treated in standard fashion by Dr. Klugman. The patient was then transferred to the Redlands Clinic and by some experimental protocol which, I guess, includes some sort of lymphocyte electrophoresis, has been placed into remission. He is not currently on any antileukemia drugs and has responded extremely well to his medical management.\nOn examination, the patient is healthy in general appearance. There is a 1.5 cm lesion on the concha of the ear, which is seen well on photograph of the left external ear. There are numerous soft lymph nodes in both sides of the neck, which I presume are related to his leukemia.");

    doc->getTree().addContentItem(DSRTypes::RT_contains, DSRTypes::VT_Text);
    doc->getTree().getCurrentContentItem().setConceptName(DSRCodedEntryValue("CODE_02", OFFIS_CODING_SCHEME_DESIGNATOR, "Diagnosis"));
    doc->getTree().getCurrentContentItem().setStringValue("Squamous cell carcinoma, relatively superficial, involving the skin of the left external ear, which is seen well on photograph of the left external ear.");

    doc->getTree().addContentItem(DSRTypes::RT_contains, DSRTypes::VT_Text);
    doc->getTree().getCurrentContentItem().setConceptName(DSRCodedEntryValue("CODE_03", OFFIS_CODING_SCHEME_DESIGNATOR, "Treatment"));
    doc->getTree().getCurrentContentItem().setStringValue("The plan of treatment is as follows: 4500 rad, 15 treatment sessions, using 100 kV radiation.\nThe reason for treatment, expected acute reaction, and remote possibility of complication was discussed with this patient at some length, and he accepted therapy as outlined.");
}
