recordTypeToName(const E_DirRecType recordType)
{
    const char *recordName = NULL;
    switch (recordType)
    {
        case ERT_root:
            recordName = "Root";
            break;
        case ERT_Curve:
            recordName = "Curve";
            break;
        case ERT_FilmBox:
            recordName = "FilmBox";
            break;
        case ERT_FilmSession:
            recordName = "FilmSession";
            break;
        case ERT_Image:
            recordName = "Image";
            break;
        case ERT_ImageBox:
            recordName = "ImageBox";
            break;
        case ERT_Interpretation:
            recordName = "Interpretation";
            break;
        case ERT_ModalityLut:
            recordName = "ModalityLUT";
            break;
        case ERT_Mrdr:
            recordName = "MRDR";
            break;
        case ERT_Overlay:
            recordName = "Overlay";
            break;
        case ERT_Patient:
            recordName = "Patient";
            break;
        case ERT_PrintQueue:
            recordName = "PrintQueue";
            break;
        case ERT_Private:
            recordName = "Private";
            break;
        case ERT_Results:
            recordName = "Results";
            break;
        case ERT_Series:
            recordName = "Series";
            break;
        case ERT_Study:
            recordName = "Study";
            break;
        case ERT_StudyComponent:
            recordName = "StudyComponent";
            break;
        case ERT_Topic:
            recordName = "Topic";
            break;
        case ERT_Visit:
            recordName = "Visit";
            break;
        case ERT_VoiLut:
            recordName = "VOILUT";
            break;
        case ERT_SRDocument:
            recordName = "SRDocument";
            break;
        case ERT_Presentation:
            recordName = "Presentation";
            break;
        case ERT_Waveform:
            recordName = "Waveform";
            break;
        case ERT_RTDose:
            recordName = "RTDose";
            break;
        case ERT_RTStructureSet:
            recordName = "RTStructureSet";
            break;
        case ERT_RTPlan:
            recordName = "RTPlan";
            break;
        case ERT_RTTreatRecord:
            recordName = "RTTreatRecord";
            break;
        case ERT_StoredPrint:
            recordName = "StoredPrint";
            break;
        case ERT_KeyObjectDoc:
            recordName = "KeyObjectDoc";
            break;
        case ERT_Registration:
            recordName = "Registration";
            break;
        case ERT_Fiducial:
            recordName = "Fiducial";
            break;
        case ERT_RawData:
            recordName = "RawData";
            break;
        case ERT_Spectroscopy:
            recordName = "Spectroscopy";
            break;
        case ERT_EncapDoc:
            recordName = "EncapDoc";
            break;
        case ERT_ValueMap:
            recordName = "ValueMap";
            break;
        case ERT_HangingProtocol:
            recordName = "HangingProtocol";
            break;
        case ERT_Stereometric:
            recordName = "Stereometric";
            break;
        case ERT_HL7StrucDoc:
            recordName = "HL7StrucDoc";
            break;
        case ERT_Palette:
            recordName = "Palette";
            break;
        case ERT_Surface:
            recordName = "Surface";
            break;
        case ERT_Measurement:
            recordName = "Measurement";
            break;
        case ERT_Implant:
            recordName = "Implant";
            break;
        case ERT_ImplantGroup:
            recordName = "ImplantGroup";
            break;
        case ERT_ImplantAssy:
            recordName = "ImplantAssy";
            break;
        default:
            recordName = "(unknown-directory-record-type)";
            break;
    }
    return recordName;
}
