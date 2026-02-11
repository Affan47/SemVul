formatTokenUid()
    {
        _uid = _item->uuid();
        switch (_valueType) {
        case FormItemToken::FormItemLabel:
            _uid.prepend(QString("%1.%2.")
                         .arg(Constants::TOKENFORM_NAMESPACE)
                         .arg(Constants::TOKENFORM_LABEL_NAMESPACE));
            break;
        case FormItemToken::FormItemTooltip:
            _uid.prepend(QString("%1.%2.")
                         .arg(Constants::TOKENFORM_NAMESPACE)
                         .arg(Constants::TOKENFORM_TOOLTIP_NAMESPACE));
            break;
        case FormItemToken::FormItemPatientModelValue:
            _uid.prepend(QString("%1.%2.%3.")
                         .arg(Constants::TOKENFORM_NAMESPACE)
                         .arg(Constants::TOKENFORM_DATA_NAMESPACE)
                         .arg(Constants::TOKENFORM_PATIENTDATA_NAMESPACE));
            break;
        case FormItemToken::FormItemPrintValue:
            _uid.prepend(QString("%1.%2.%3.")
                         .arg(Constants::TOKENFORM_NAMESPACE)
                         .arg(Constants::TOKENFORM_DATA_NAMESPACE)
                         .arg(Constants::TOKENFORM_PRINTDATA_NAMESPACE));
            break;
        case FormItemToken::FormItemDataValue:
            _uid.prepend(QString("%1.%2.%3.")
                         .arg(Constants::TOKENFORM_NAMESPACE)
                         .arg(Constants::TOKENFORM_DATA_NAMESPACE)
                         .arg(Constants::TOKENFORM_ITEMDATA_NAMESPACE));
            break;
        default: LOG_ERROR_FOR("FormItemToken", "No namespace for this ValueType. Please check the code.");
        }
    }
