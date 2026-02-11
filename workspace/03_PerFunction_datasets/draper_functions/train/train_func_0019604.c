AcpiPsCreateScopeOp (
    void)
{
    ACPI_PARSE_OBJECT       *ScopeOp;


    ScopeOp = AcpiPsAllocOp (AML_SCOPE_OP);
    if (!ScopeOp)
    {
        return (NULL);
    }

    ScopeOp->Named.Name = ACPI_ROOT_NAME;
    return (ScopeOp);
}
