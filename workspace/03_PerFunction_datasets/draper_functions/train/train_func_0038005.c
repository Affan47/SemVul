get_schema_name(int version)
{
    if (version < 0 || version >= all_schemas) {
        return "unknown";
    }
    return known_schemas[version].name;
}
