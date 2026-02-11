AcpiNsWrapWithPackage (
    ACPI_EVALUATE_INFO      *Info,
    ACPI_OPERAND_OBJECT     *OriginalObject,
    ACPI_OPERAND_OBJECT     **ObjDescPtr)
{
    ACPI_OPERAND_OBJECT     *PkgObjDesc;


    ACPI_FUNCTION_NAME (NsWrapWithPackage);


    PkgObjDesc = AcpiUtCreatePackageObject (1);
    if (!PkgObjDesc)
    {
        return (AE_NO_MEMORY);
    }

    PkgObjDesc->Package.Elements[0] = OriginalObject;

    ACPI_DEBUG_PRINT ((ACPI_DB_REPAIR,
        "%s: Wrapped %s with expected Package object\n",
        Info->FullPathname, AcpiUtGetObjectTypeName (OriginalObject)));


    *ObjDescPtr = PkgObjDesc;
    Info->ReturnFlags |= ACPI_OBJECT_REPAIRED | ACPI_OBJECT_WRAPPED;
    return (AE_OK);
}
