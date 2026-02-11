operator==(const MappingKey& other) const
{
    if (IDTableBase::MappingKey::caseNormalizationMode == IDS_CaseSensitive)
        return !strcmp(str, other.str);
    else
        return !strcasecmp(str, other.str);
}
